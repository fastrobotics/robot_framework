/**
 * @file DepthCameraPipelineSubsystem.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-10-05
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <Infrastructure/Logger.hpp>
#include <PointCloudMsg.hpp>
#include <SensorHealthMonitorProcess.hpp>
#include <SensorInputHandlerProcess.hpp>
#include <string>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem {
    class DepthCameraPipelineSubsystem {
       public:
        bool init();
        bool newPointCloud(fast::rf::messages::SensorMsgs::PointCloudMsg msg, std::string sensorName);
        std::string pretty();
        bool update(double currentTimeSec);

       private:
        SensorHealthMonitor::SensorHealthMonitorProcess m_sensorInputHandlerProcess;
        SensorHealthMonitor::SensorHealthMonitorProcess m_sensorHealthMonitorProcess;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem