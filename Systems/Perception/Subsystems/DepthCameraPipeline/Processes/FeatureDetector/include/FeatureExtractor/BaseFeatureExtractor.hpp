/**
 * @file BaseFeatureExtractor.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-10-13
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <FeatureExtractor/IFeatureExtractor.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector {
    class BaseFeatureExtractor : public IFeatureExtractor {
       public:
        bool init() override { return this->init(); }
        bool update(double currentTimeSec) { return this->update(currentTimeSec); }
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector