/**
 * @file IObjectExtractor.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-10-19
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include <cstdint>
#include <vector>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector {
    struct DiscoveredObject {
        uint64_t id;
    };
    class IObjectExtractor {
       public:
        virtual bool init() = 0;
        virtual bool setConfig(double clusterToleranceDeg, uint64_t minClusterSize) = 0;
        virtual std::vector<DiscoveredObject> extractObjects(
            const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud, const pcl::PointCloud<pcl::Normal>::Ptr& normals,
            const pcl::PointCloud<pcl::FPFHSignature33>::Ptr& fpfh_features) = 0;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector