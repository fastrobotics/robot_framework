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
#include <Infrastructure/Logger.hpp>
#include <ObjectExtractor/IObjectExtractor.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector {
    class BaseObjectExtractor : public IObjectExtractor {
       public:
        bool init() override;
        bool setConfig(double clusterToleranceDeg, uint64_t minClusterSize) override;
        static fast::rf::messages::VisionMsgs::Detection3DMsg convert(double time_stamp,
                                                                      IObjectExtractor::DiscoveredObject object);

       protected:
        double m_clusterToleranceDeg;
        double m_minClusterSize;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector