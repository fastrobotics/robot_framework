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

#include <Detection3DMsg.hpp>
#include <Eigen/Dense>
#include <PointCloudMsg.hpp>
#include <cstddef>
#include <cstdint>
#include <vector>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector {

    class IObjectExtractor {
       public:
        /**
         * @brief Describes one segmented object cluster and its derived geometry/features.
         *
         * The identifier is local to one extraction result, and all positions and distances
         * use the input cloud's coordinate frame and units.
         */
        struct DiscoveredObject {
            /// Sequential identifier assigned within an extraction result; starts at zero.
            uint64_t id;
            /// Number of input points assigned to this cluster (the cluster cloud's size).
            std::size_t point_count;
            /// Cluster's arithmetic 3D centroid; x, y, z are the first three components.
            /// Uses the input point cloud's coordinate frame.
            Eigen::Vector4f centroid;
            /// The three oriented bounding-box extents along its local axes, in input-cloud units.
            Eigen::Vector3f dimensions;
            /// Orientation of the cluster's oriented bounding box relative to the input cloud frame.
            Eigen::Matrix3f rotation_matrix;
            /// 33-bin cluster descriptor: the per-bin mean of its points' FPFH histograms.
            Eigen::VectorXf global_fpfh;
            /// RGB point cloud containing the points assigned to this segmented cluster.
            pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_cluster;
            std::string pretty() {
                std::string str = "Object: ID: " + std::to_string(id) + " Point Count: " + std::to_string(point_count) +
                                  " Size: X: " + std::to_string(dimensions.x()) +
                                  " Y: " + std::to_string(dimensions.y()) + " Z: " + std::to_string(dimensions.z());
                return str;
            }
        };
        virtual bool init() = 0;
        virtual bool setConfig(double clusterToleranceDeg, uint64_t minClusterSize) = 0;
        virtual std::vector<fast::rf::messages::VisionMsgs::Detection3DMsg> extractObjects(
            fast::rf::messages::SensorMsgs::PointCloudMsg sensorCloud) = 0;

       protected:
        virtual std::vector<DiscoveredObject> extractObjects(
            const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud, const pcl::PointCloud<pcl::Normal>::Ptr& normals,
            const pcl::PointCloud<pcl::FPFHSignature33>::Ptr& fpfh_features) = 0;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector