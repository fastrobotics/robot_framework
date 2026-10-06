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
#include <ReadyToArmStatusMsg.hpp>
#include <SensorHealthMonitorProcess.hpp>
#include <SensorInputHandlerProcess.hpp>
#include <memory>
#include <string>
#include <unordered_map>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem {
    class DepthCameraPipelineSubsystem {
       public:
        DepthCameraPipelineSubsystem()
            : m_sensorInputHandlerProcess(std::make_shared<fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::
                                                               SensorInputHandler::SensorInputHandlerProcess>()),
              m_sensorHealthMonitorProcess(std::make_shared<fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::
                                                                SensorHealthMonitor::SensorHealthMonitorProcess>()) {
            m_pipeline["input_handler"] = m_sensorInputHandlerProcess;
            m_pipeline["health_monitor"] = m_sensorHealthMonitorProcess;
            m_readyToArm.systemID = fast::rf::PerceptionSystem::SYSTEM_ID;
            m_readyToArm.subsystemID = fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SUBSYSTEM_ID;
            m_readyToArm.processID = 0;  // Entire Subsystem
        }
        bool init();
        bool addSignalToMonitor(std::string signalName, std::string datatype, double expectedRateHz,
                                double rateTolerancePerc) {
            return m_sensorHealthMonitorProcess->addSignalToMonitor(signalName, datatype, expectedRateHz,
                                                                    rateTolerancePerc);
        }
        bool newPointCloud(fast::rf::messages::SensorMsgs::PointCloudMsg msg, std::string sensorName);
        std::string pretty();
        bool update(double currentTimeSec);
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() { return m_readyToArm; }
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics();

       private:
        std::shared_ptr<
            fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorInputHandler::SensorInputHandlerProcess>
            m_sensorInputHandlerProcess;
        std::shared_ptr<
            fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorHealthMonitor::SensorHealthMonitorProcess>
            m_sensorHealthMonitorProcess;

        std::unordered_map<std::string, std::shared_ptr<fast::rf::IProcess>> m_pipeline;
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg m_readyToArm;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem