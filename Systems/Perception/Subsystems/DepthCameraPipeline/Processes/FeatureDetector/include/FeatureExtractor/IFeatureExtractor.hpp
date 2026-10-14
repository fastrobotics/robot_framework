/**
 * @file IFeatureExtractor.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-10-13
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <PointCloudMsg.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector {
    struct FeatureExtractionContainer {
        fast::rf::messages::SensorMsgs::PointCloudMsg cloud;
        bool wereFeaturesExtracted{false};
    };
    class IFeatureExtractor {
       public:
        IFeatureExtractor() = default;
        virtual ~IFeatureExtractor() = default;
        virtual bool init() = 0;
        virtual bool update(double currentTimeSec) = 0;
        virtual std::string pretty() = 0;
        virtual FeatureExtractionContainer extractFeatures(
            fast::rf::messages::SensorMsgs::PointCloudMsg pointCloud) = 0;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector