/**
 * @file BaseObjectExtractor.cpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-10-19
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <ObjectExtractor/BaseObjectExtractor.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector {
    bool BaseObjectExtractor::init() { return true; }
    bool BaseObjectExtractor::setConfig(double clusterToleranceDeg, uint64_t minClusterSize) {
        m_clusterToleranceDeg = clusterToleranceDeg;
        m_minClusterSize = minClusterSize;
        return true;
    }
    fast::rf::messages::VisionMsgs::Detection3DMsg BaseObjectExtractor::convert(
        double time_stamp, IObjectExtractor::DiscoveredObject object) {
        fast::rf::messages::VisionMsgs::Detection3DMsg detection;
        fast::rf::messages::VisionMsgs::ObjectHypothesisWithPoseMsg hypothesis;
        hypothesis.id = object.id;
        Eigen::Vector3f euler = object.rotation_matrix.eulerAngles(0, 1, 2);  // X-Y-Z
        hypothesis.pose.pose.orientation.roll = euler[0];                     // X rotation
        hypothesis.pose.pose.orientation.pitch = euler[1];                    // Y rotation
        hypothesis.pose.pose.orientation.yaw = euler[2];                      // Z rotation
        hypothesis.pose.pose.position.x = object.centroid.x();
        hypothesis.pose.pose.position.y = object.centroid.y();
        hypothesis.pose.pose.position.z = object.centroid.z();
        detection.results.push_back(hypothesis);
        detection.bbox.center.position = hypothesis.pose.pose.position;
        detection.bbox.center.orientation = hypothesis.pose.pose.orientation;
        detection.bbox.size.x = object.dimensions.x();
        detection.bbox.size.y = object.dimensions.y();
        detection.bbox.size.z = object.dimensions.z();
        detection.source_cloud.point_cloud = object.cloud_cluster;
        detection.time_stamp = time_stamp;
        return detection;
    }
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector