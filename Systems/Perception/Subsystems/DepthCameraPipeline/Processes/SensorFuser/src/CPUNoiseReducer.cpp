#include <pcl/common/io.h>
#include <pcl/search/kdtree.h>

#include <CPUNoiseReducer.hpp>
#include <cstddef>
#include <cstdint>
#include <utility>

#include "NoiseReducerPipeline.hpp"

namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    namespace {
        void radiusOutlierRemovalParallel(const detail::Cloud::ConstPtr& input, detail::Cloud& output, double radius,
                                          int min_neighbors) {
            pcl::search::KdTree<detail::Point>::Ptr tree(new pcl::search::KdTree<detail::Point>(false));
            tree->setInputCloud(input);

            const int required_neighbors = min_neighbors + 1;
            const double radius_squared = radius * radius;
            std::vector<uint8_t> is_inlier(input->size(), 0);
            const auto point_count = static_cast<std::ptrdiff_t>(input->size());

#pragma omp parallel
            {
                pcl::Indices neighbor_indices;
                std::vector<float> neighbor_distances;

#pragma omp for schedule(static)
                for (std::ptrdiff_t index = 0; index < point_count; ++index) {
                    const int neighbor_count = tree->nearestKSearch(static_cast<int>(index), required_neighbors,
                                                                    neighbor_indices, neighbor_distances);
                    if (neighbor_count == required_neighbors &&
                        neighbor_distances[neighbor_count - 1] <= radius_squared) {
                        is_inlier[static_cast<std::size_t>(index)] = 1;
                    }
                }
            }

            pcl::Indices inlier_indices;
            inlier_indices.reserve(input->size());
            for (std::size_t index = 0; index < is_inlier.size(); ++index) {
                if (is_inlier[index] != 0)
                    inlier_indices.push_back(static_cast<int>(index));
            }
            pcl::copyPointCloud(*input, inlier_indices, output);
        }
    }  // namespace

    bool CPUNoiseReducer::init() { return isValidNoiseReducerConfig(m_config); }

    bool CPUNoiseReducer::setConfig(const NoiseReducerConfig& config) {
        if (!isValidNoiseReducerConfig(config))
            return false;
        m_config = config;
        return true;
    }

    fast::rf::messages::SensorMsgs::PointCloudMsg CPUNoiseReducer::reduceNoise(
        const fast::rf::messages::SensorMsgs::PointCloudMsg& input) {
        if (!input.point_cloud)
            return detail::emptyResult(input.time_stamp);
        if (input.point_cloud->empty())
            return detail::passthroughResult(input);

        auto downsampled_cloud = detail::prepareCloud(input.point_cloud, m_config);
        if (downsampled_cloud->empty())
            return detail::emptyResult(input.time_stamp, input.point_cloud);

        detail::Cloud::Ptr filtered_cloud(new detail::Cloud());
        radiusOutlierRemovalParallel(downsampled_cloud, *filtered_cloud, m_config.radius_m,
                                     static_cast<int>(m_config.minNeighborCount));
        filtered_cloud->is_dense = true;

        fast::rf::messages::SensorMsgs::PointCloudMsg result;
        result.time_stamp = input.time_stamp;
        result.point_cloud = std::move(filtered_cloud);
        return result;
    }
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser
