#include <pcl/filters/filter.h>
#include <pcl/filters/voxel_grid.h>

#include <Infrastructure/Logger.hpp>
#include <NoiseReducer/BaseNoiseReducer.hpp>
#include <exception>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    using Cloud = pcl::PointCloud<pcl::PointXYZRGB>;

    bool isValidNoiseReducerConfig(const NoiseReducerConfig& config) {
        constexpr double max_float = std::numeric_limits<float>::max();
        if (!std::isfinite(config.voxelSize_m) || config.voxelSize_m <= 0.0 || config.voxelSize_m > max_float ||
            !std::isfinite(config.radius_m) || config.radius_m <= 0.0 || config.radius_m > max_float ||
            config.minNeighborCount >= static_cast<uint64_t>(std::numeric_limits<int>::max()))
            return false;

        const float voxel_size = static_cast<float>(config.voxelSize_m);
        const float radius = static_cast<float>(config.radius_m);
        const float radius_squared = radius * radius;
        return std::isfinite(voxel_size) && voxel_size > 0.0f && std::isfinite(radius) && radius > 0.0f &&
               std::isfinite(1.0f / radius) && radius_squared > 0.0f && std::isfinite(radius_squared);
    }

    bool BaseNoiseReducer::setConfig(const NoiseReducerConfig& config) {
        if (!isValidNoiseReducerConfig(config))
            return false;
        m_config = config;
        m_initialized = false;
        return true;
    }

    bool BaseNoiseReducer::init() {
        m_initialized = isValidNoiseReducerConfig(m_config);
        return m_initialized;
    }

    fast::rf::messages::SensorMsgs::PointCloudMsg BaseNoiseReducer::reduceNoise(
        const fast::rf::messages::SensorMsgs::PointCloudMsg& input) {
        if (!m_initialized)
            throw std::logic_error("NoiseReducer must be initialized with a valid configuration.");
        if (!input.point_cloud) {
            fast::rf::Logger::logError("PointCloudMsg contains a null PCL point cloud.");
            return emptyResult(input.time_stamp);
        }
        if (input.point_cloud->empty())
            return passthroughResult(input);

        auto downsampled_cloud = prepareCloud(input.point_cloud);
        if (downsampled_cloud->empty())
            return emptyResult(input.time_stamp, input.point_cloud);

        try {
            auto filtered_cloud = filterCloud(downsampled_cloud);
            if (!filtered_cloud)
                throw std::runtime_error("NoiseReducer backend returned a null point cloud.");
            filtered_cloud->header = downsampled_cloud->header;
            filtered_cloud->sensor_origin_ = downsampled_cloud->sensor_origin_;
            filtered_cloud->sensor_orientation_ = downsampled_cloud->sensor_orientation_;
            fast::rf::messages::SensorMsgs::PointCloudMsg result;
            result.time_stamp = input.time_stamp;
            result.point_cloud = std::move(filtered_cloud);
            if (result.size() == 0) {
                fast::rf::Logger::logWarn("Noise Reducer removed all points from Cloud!");
            }
            return result;
        } catch (const std::exception& error) {
            fast::rf::Logger::logError("NoiseReducer backend failed: " + std::string(error.what()));
            throw;
        }
    }

    Cloud::Ptr BaseNoiseReducer::prepareCloud(const Cloud::ConstPtr& input) const {
        Cloud::Ptr clean_cloud(new Cloud());
        std::vector<int> valid_indices;
        pcl::removeNaNFromPointCloud(*input, *clean_cloud, valid_indices);
        clean_cloud->is_dense = true;
        if (clean_cloud->empty())
            return clean_cloud;

        Cloud::Ptr downsampled_cloud(new Cloud());
        pcl::VoxelGrid<pcl::PointXYZRGB> voxel_filter;
        voxel_filter.setInputCloud(clean_cloud);
        const float leaf_size = static_cast<float>(m_config.voxelSize_m);
        voxel_filter.setLeafSize(leaf_size, leaf_size, leaf_size);
        voxel_filter.filter(*downsampled_cloud);
        downsampled_cloud->is_dense = true;
        return downsampled_cloud;
    }

    fast::rf::messages::SensorMsgs::PointCloudMsg BaseNoiseReducer::emptyResult(double timestamp,
                                                                                const Cloud::ConstPtr& source) const {
        fast::rf::messages::SensorMsgs::PointCloudMsg result;
        result.time_stamp = timestamp;
        result.point_cloud.reset(new Cloud());
        result.point_cloud->width = 0;
        result.point_cloud->height = 1;
        result.point_cloud->is_dense = true;
        if (source) {
            result.point_cloud->header = source->header;
            result.point_cloud->sensor_origin_ = source->sensor_origin_;
            result.point_cloud->sensor_orientation_ = source->sensor_orientation_;
        }
        return result;
    }

    fast::rf::messages::SensorMsgs::PointCloudMsg BaseNoiseReducer::passthroughResult(
        const fast::rf::messages::SensorMsgs::PointCloudMsg& input) {
        return input;
    }
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser
