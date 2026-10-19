/**
 * @file BaseObjectExtractor.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-10-19
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <ObjectExtractor/IObjectExtractor.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector {
    class BaseObjectExtractor : public IObjectExtractor {
       public:
        bool init() override;
        bool setConfig(double clusterToleranceDeg, uint64_t minClusterSize) override;

       protected:
        double m_clusterToleranceDeg;
        double m_minClusterSize;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector