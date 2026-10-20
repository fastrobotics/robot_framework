/**
 * @file ObjectExtractorCPU.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-10-18
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <ObjectExtractor/BaseObjectExtractor.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector {
    class ObjectExtractorCPU : public BaseObjectExtractor {
       public:
        std::vector<fast::rf::messages::VisionMsgs::Detection3DMsg> extractObjects(
            fast::rf::messages::SensorMsgs::PointCloudMsg sensorCloud) override;

       private:
        std::vector<IObjectExtractor::DiscoveredObject> extractObjects(
            const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud, const pcl::PointCloud<pcl::Normal>::Ptr& normals,
            const pcl::PointCloud<pcl::FPFHSignature33>::Ptr& fpfh_features) override;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector