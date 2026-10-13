/**
 * @file FeatureExtractorCPU.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-10-13
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <FeatureExtractor/BaseFeatureExtractor.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector {
    class FeatureExtractorCPU : public BaseFeatureExtractor {
       public:
        bool init() override;
        bool update(double currentTimeSec) override;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector