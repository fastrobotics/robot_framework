/**
 * @file Combiner.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-10-08
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <PointCloudMsg.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    class Combiner {
       public:
        bool init();
        bool newPointCloud(fast::rf::messages::SensorMsgs::PointCloudMsg msg, uint8_t sensorIndex);
        bool isCombinedPointCloudAvailable();
        fast::rf::messages::SensorMsgs::PointCloudMsg getCombinedPointCloud();

       private:
        struct CombinerContainer {
            bool ready{false};
            fast::rf::messages::SensorMsgs::PointCloudMsg combinedPointCloud;
        };
        CombinerContainer m_combinedContainer;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser