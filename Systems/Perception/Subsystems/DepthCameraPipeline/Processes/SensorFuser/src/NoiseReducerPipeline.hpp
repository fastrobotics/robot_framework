#pragma once

#include <pcl/filters/filter.h>
#include <pcl/filters/voxel_grid.h>

#include <INoiseReducer.hpp>
#include <memory>
#include <vector>

namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser::detail {
    using Point = pcl::PointXYZRGB;
    using Cloud = pcl::PointCloud<Point>;

    inline Cloud::Ptr makeEmptyCloud() {
        Cloud::Ptr cloud(new Cloud());
        cloud->width = 0;
        cloud->height = 1;
        cloud->is_dense = true;
        return cloud;
    }

    inline Cloud::Ptr prepareCloud(const Cloud::ConstPtr& input, const NoiseReducerConfig& config) {
        Cloud::Ptr clean_cloud(new Cloud());
        std::vector<int> valid_indices;
        pcl::removeNaNFromPointCloud(*input, *clean_cloud, valid_indices);
        clean_cloud->is_dense = true;
        if (clean_cloud->empty())
            return clean_cloud;

        Cloud::Ptr downsampled_cloud(new Cloud());
        pcl::VoxelGrid<Point> voxel_filter;
        voxel_filter.setInputCloud(clean_cloud);
        const float leaf_size = static_cast<float>(config.voxelSize_m);
        voxel_filter.setLeafSize(leaf_size, leaf_size, leaf_size);
        voxel_filter.filter(*downsampled_cloud);
        downsampled_cloud->is_dense = true;
        return downsampled_cloud;
    }

    inline fast::rf::messages::SensorMsgs::PointCloudMsg emptyResult(
        double timestamp, const Cloud::ConstPtr& source = Cloud::ConstPtr()) {
        fast::rf::messages::SensorMsgs::PointCloudMsg result;
        result.time_stamp = timestamp;
        result.point_cloud = makeEmptyCloud();
        result.point_cloud->is_dense = true;
        if (source) {
            result.point_cloud->header = source->header;
            result.point_cloud->sensor_origin_ = source->sensor_origin_;
            result.point_cloud->sensor_orientation_ = source->sensor_orientation_;
        }
        return result;
    }

    inline fast::rf::messages::SensorMsgs::PointCloudMsg passthroughResult(
        const fast::rf::messages::SensorMsgs::PointCloudMsg& input) {
        return input;
    }
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser::detail
