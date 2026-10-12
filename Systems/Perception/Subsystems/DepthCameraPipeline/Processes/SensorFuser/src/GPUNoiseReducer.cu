#include <cuda_runtime.h>

#include <GPUNoiseReducer.hpp>
#include "NoiseReducerPipeline.hpp"
#include <thrust/device_vector.h>
#include <thrust/sort.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    namespace {
        struct GpuPoint {
            float x;
            float y;
            float z;
        };

        void checkCuda(cudaError_t status, const char* operation) {
            if (status != cudaSuccess)
                throw std::runtime_error(std::string(operation) + ": " + cudaGetErrorString(status));
        }

        __device__ unsigned long long linearCellKey(unsigned long long x, unsigned long long y,
                                                    unsigned long long z, unsigned long long cells_x,
                                                    unsigned long long cells_y) {
            return x + cells_x * (y + cells_y * z);
        }

        __global__ void buildCellKeys(const GpuPoint* points, unsigned long long* keys,
                                      unsigned long long* point_indices, std::size_t point_count, float min_x,
                                      float min_y, float min_z, float inverse_cell_size,
                                      unsigned long long cells_x, unsigned long long cells_y) {
            const std::size_t index = static_cast<std::size_t>(blockIdx.x) * blockDim.x + threadIdx.x;
            if (index >= point_count)
                return;
            const GpuPoint point = points[index];
            const auto cell_x = static_cast<unsigned long long>(floorf((point.x - min_x) * inverse_cell_size));
            const auto cell_y = static_cast<unsigned long long>(floorf((point.y - min_y) * inverse_cell_size));
            const auto cell_z = static_cast<unsigned long long>(floorf((point.z - min_z) * inverse_cell_size));
            keys[index] = linearCellKey(cell_x, cell_y, cell_z, cells_x, cells_y);
            point_indices[index] = index;
        }

        __device__ std::size_t findCellStart(const unsigned long long* sorted_keys, std::size_t point_count,
                                             unsigned long long target_key) {
            std::size_t first = 0;
            std::size_t last = point_count;
            while (first < last) {
                const std::size_t middle = first + (last - first) / 2;
                if (sorted_keys[middle] < target_key)
                    first = middle + 1;
                else
                    last = middle;
            }
            return first;
        }

        __global__ void classifyRadiusNeighbors(const GpuPoint* points, const unsigned long long* sorted_keys,
                                                const unsigned long long* sorted_indices, std::uint8_t* inliers,
                                                std::size_t point_count, float min_x, float min_y, float min_z,
                                                float inverse_cell_size, double radius_squared,
                                                unsigned long long cells_x, unsigned long long cells_y,
                                                unsigned long long cells_z, unsigned long long required_neighbors) {
            const std::size_t point_index = static_cast<std::size_t>(blockIdx.x) * blockDim.x + threadIdx.x;
            if (point_index >= point_count)
                return;

            const GpuPoint point = points[point_index];
            const auto center_x =
                static_cast<long long>(floorf((point.x - min_x) * inverse_cell_size));
            const auto center_y =
                static_cast<long long>(floorf((point.y - min_y) * inverse_cell_size));
            const auto center_z =
                static_cast<long long>(floorf((point.z - min_z) * inverse_cell_size));
            unsigned long long neighbor_count = 0;

            for (int dz = -1; dz <= 1 && neighbor_count < required_neighbors; ++dz) {
                const long long z = center_z + dz;
                if (z < 0 || static_cast<unsigned long long>(z) >= cells_z)
                    continue;
                for (int dy = -1; dy <= 1 && neighbor_count < required_neighbors; ++dy) {
                    const long long y = center_y + dy;
                    if (y < 0 || static_cast<unsigned long long>(y) >= cells_y)
                        continue;
                    for (int dx = -1; dx <= 1 && neighbor_count < required_neighbors; ++dx) {
                        const long long x = center_x + dx;
                        if (x < 0 || static_cast<unsigned long long>(x) >= cells_x)
                            continue;
                        const auto key = linearCellKey(static_cast<unsigned long long>(x),
                                                       static_cast<unsigned long long>(y),
                                                       static_cast<unsigned long long>(z), cells_x, cells_y);
                        std::size_t candidate = findCellStart(sorted_keys, point_count, key);
                        while (candidate < point_count && sorted_keys[candidate] == key &&
                               neighbor_count < required_neighbors) {
                            const GpuPoint other = points[sorted_indices[candidate]];
                            const float delta_x = point.x - other.x;
                            const float delta_y = point.y - other.y;
                            const float delta_z = point.z - other.z;
                            const float distance_squared =
                                delta_x * delta_x + delta_y * delta_y + delta_z * delta_z;
                            if (static_cast<double>(distance_squared) <= radius_squared)
                                ++neighbor_count;
                            ++candidate;
                        }
                    }
                }
            }
            inliers[point_index] = neighbor_count >= required_neighbors ? 1 : 0;
        }

        detail::Cloud::Ptr radiusFilterOnGpu(const detail::Cloud::ConstPtr& input,
                                             const NoiseReducerConfig& config) {
            const std::size_t point_count = input->size();
            const auto required_neighbors = config.minNeighborCount + 1;
            detail::Cloud::Ptr output(new detail::Cloud(*input));
            output->clear();
            output->width = 0;
            output->height = 1;
            output->is_dense = true;
            if (required_neighbors > point_count) {
                return output;
            }

            std::vector<GpuPoint> host_points;
            host_points.reserve(point_count);
            float min_x = std::numeric_limits<float>::max();
            float min_y = std::numeric_limits<float>::max();
            float min_z = std::numeric_limits<float>::max();
            float max_x = std::numeric_limits<float>::lowest();
            float max_y = std::numeric_limits<float>::lowest();
            float max_z = std::numeric_limits<float>::lowest();
            for (const auto& point : input->points) {
                host_points.push_back({point.x, point.y, point.z});
                min_x = std::min(min_x, point.x);
                min_y = std::min(min_y, point.y);
                min_z = std::min(min_z, point.z);
                max_x = std::max(max_x, point.x);
                max_y = std::max(max_y, point.y);
                max_z = std::max(max_z, point.z);
            }

            const double inverse_cell_size = 1.0 / config.radius_m;
            constexpr double max_cell_count = static_cast<double>(std::numeric_limits<long long>::max() - 2);
            const auto getCellCount = [inverse_cell_size](float minimum, float maximum) {
                return std::floor((static_cast<double>(maximum) - minimum) * inverse_cell_size) + 2.0;
            };
            const double cells_x_double = getCellCount(min_x, max_x);
            const double cells_y_double = getCellCount(min_y, max_y);
            const double cells_z_double = getCellCount(min_z, max_z);
            if (cells_x_double >= max_cell_count || cells_y_double >= max_cell_count ||
                cells_z_double >= max_cell_count)
                throw std::runtime_error("GPU radius filter grid exceeds supported coordinate range.");

            const auto cells_x = static_cast<unsigned long long>(cells_x_double);
            const auto cells_y = static_cast<unsigned long long>(cells_y_double);
            const auto cells_z = static_cast<unsigned long long>(cells_z_double);
            constexpr auto max_key = std::numeric_limits<unsigned long long>::max();
            if (cells_x > max_key / cells_y || cells_x * cells_y > max_key / cells_z)
                throw std::runtime_error("GPU radius filter grid key range overflows.");

            thrust::device_vector<GpuPoint> device_points(host_points.begin(), host_points.end());
            thrust::device_vector<unsigned long long> sorted_keys(point_count);
            thrust::device_vector<unsigned long long> sorted_indices(point_count);
            thrust::device_vector<std::uint8_t> device_inliers(point_count);

            constexpr int threads_per_block = 256;
            const std::size_t blocks_per_grid_size =
                (point_count + threads_per_block - 1) / threads_per_block;
            if (blocks_per_grid_size > static_cast<std::size_t>(std::numeric_limits<int>::max()))
                throw std::runtime_error("GPU radius filter input exceeds the supported launch grid.");
            const int blocks_per_grid = static_cast<int>(blocks_per_grid_size);
            const float inverse_cell_size_float = static_cast<float>(inverse_cell_size);
            buildCellKeys<<<blocks_per_grid, threads_per_block>>>(
                thrust::raw_pointer_cast(device_points.data()), thrust::raw_pointer_cast(sorted_keys.data()),
                thrust::raw_pointer_cast(sorted_indices.data()), point_count, min_x, min_y, min_z,
                inverse_cell_size_float, cells_x, cells_y);
            checkCuda(cudaGetLastError(), "Launching GPU radius-filter cell-index kernel");
            thrust::sort_by_key(sorted_keys.begin(), sorted_keys.end(), sorted_indices.begin());

            classifyRadiusNeighbors<<<blocks_per_grid, threads_per_block>>>(
                thrust::raw_pointer_cast(device_points.data()), thrust::raw_pointer_cast(sorted_keys.data()),
                thrust::raw_pointer_cast(sorted_indices.data()), thrust::raw_pointer_cast(device_inliers.data()),
                point_count, min_x, min_y, min_z, inverse_cell_size_float,
                config.radius_m * config.radius_m, cells_x, cells_y, cells_z, required_neighbors);
            checkCuda(cudaGetLastError(), "Launching GPU radius-neighbor classification kernel");

            std::vector<std::uint8_t> host_inliers(point_count);
            checkCuda(cudaMemcpy(host_inliers.data(), thrust::raw_pointer_cast(device_inliers.data()),
                                 point_count * sizeof(std::uint8_t), cudaMemcpyDeviceToHost),
                      "Copying GPU radius-filter results to host");

            output->points.reserve(point_count);
            for (std::size_t index = 0; index < point_count; ++index) {
                if (host_inliers[index] != 0)
                    output->points.push_back(input->points[index]);
            }
            output->width = static_cast<std::uint32_t>(output->points.size());
            output->height = 1;
            output->is_dense = true;
            return output;
        }
    }  // namespace

    bool GPUNoiseReducer::isAvailable() {
        int device_count = 0;
        return cudaGetDeviceCount(&device_count) == cudaSuccess && device_count > 0;
    }

    bool GPUNoiseReducer::init() {
        m_initialized = false;
        int device_count = 0;
        const cudaError_t count_status = cudaGetDeviceCount(&device_count);
        if (count_status != cudaSuccess || device_count == 0)
            return false;
        checkCuda(cudaSetDevice(0), "Selecting CUDA device 0");
        m_initialized = true;
        return true;
    }

    bool GPUNoiseReducer::setConfig(const NoiseReducerConfig& config) {
        if (!isValidNoiseReducerConfig(config))
            return false;
        m_config = config;
        return true;
    }

    fast::rf::messages::SensorMsgs::PointCloudMsg GPUNoiseReducer::reduceNoise(
        const fast::rf::messages::SensorMsgs::PointCloudMsg& input) {
        if (!m_initialized)
            throw std::logic_error("GPU NoiseReducer has not been initialized.");
        if (!input.point_cloud)
            return detail::emptyResult(input.time_stamp);
        if (input.point_cloud->empty())
            return detail::passthroughResult(input);

        auto downsampled_cloud = detail::prepareCloud(input.point_cloud, m_config);
        if (downsampled_cloud->empty())
            return detail::emptyResult(input.time_stamp, input.point_cloud);

        checkCuda(cudaSetDevice(0), "Selecting CUDA device 0 for NoiseReducer processing");
        auto filtered_cloud = radiusFilterOnGpu(downsampled_cloud, m_config);
        fast::rf::messages::SensorMsgs::PointCloudMsg result;
        result.time_stamp = input.time_stamp;
        result.point_cloud = std::move(filtered_cloud);
        return result;
    }
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser
