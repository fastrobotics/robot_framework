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
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector {
    class IFeatureExtractor {
       public:
        IFeatureExtractor() = default;
        virtual ~IFeatureExtractor() = default;
        virtual bool init() = 0;
        virtual bool update(double currentTimeSec) = 0;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector