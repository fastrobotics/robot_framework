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
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector