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

#include <Eigen/Dense>
#include <cstddef>
#include <cstdint>
#include <vector>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector {
    struct DiscoveredObject {
        uint64_t id;
        std::size_t point_count;
        Eigen::Vector4f centroid;
        Eigen::Vector3f dimensions;
        Eigen::Matrix3f rotation_matrix;
        Eigen::VectorXf global_fpfh;
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_cluster;
        std::string pretty() {
            std::string str = "Object: ID: " + std::to_string(id) + " Point Count: " + std::to_string(point_count) +
                              " Size: X: " + std::to_string(dimensions.x()) + " Y: " + std::to_string(dimensions.y()) +
                              " Z: " + std::to_string(dimensions.z());
            return str;
        }
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