#include <DepthCameraPipelineSubsystem.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem {
    bool DepthCameraPipelineSubsystem::init() {
        if (m_sensorHealthMonitorProcess->init() == false) {
            fast::rf::Logger::logError("Unable to initialize Sensor Health Monitor!");
            return false;
        }
        if (m_sensorInputHandlerProcess->init() == false) {
            fast::rf::Logger::logError("Unable to initialize Sensor Input Handler!");
            return false;
        }
        if (m_sensorFuserProcess->init() == false) {
            fast::rf::Logger::logError("Unable to initialize Sensor Fuser!");
            return false;
        }
        return true;
    }
    std::string DepthCameraPipelineSubsystem::pretty() {
        std::string str = "\n--- Depth Camera Pipeline Subsystem---\n";
        str += "\tReady To Arm: " + std::to_string(m_readyToArm.ready_to_arm) + "\n";
        for (auto process : m_pipeline) {
            str += process.second->pretty();
        }
        return str;
    }
    bool DepthCameraPipelineSubsystem::newPointCloud(fast::rf::messages::SensorMsgs::PointCloudMsg msg,
                                                     std::string sensorName) {
        if (m_sensorHealthMonitorProcess.get()->newPointCloud(sensorName, msg) == false) {
            fast::rf::Logger::logWarn("Unable to process Sensor Point Cloud Signal: " + sensorName);
            return false;
        }
        auto convertedCloud = m_sensorInputHandlerProcess.get()->newPointCloud(msg);
        if (!m_sensorFuserProcess->newPointCloud(convertedCloud, 0)) {
            fast::rf::Logger::logWarn("Unable to send Point Cloud to Sensor Fuser: " + sensorName);
            return false;
        }
        return true;
    }
    fast::rf::messages::SensorMsgs::PointCloudMsg DepthCameraPipelineSubsystem::getFusedPointCloud() {
        return m_sensorFuserProcess->getFusedPointCloud();
    }

    bool DepthCameraPipelineSubsystem::update(double currentTimeSec) {
        bool readyToArmFlag = true;
        for (auto& process : m_pipeline) {
            bool status = process.second->update(currentTimeSec);
            if (status == false) {
                fast::rf::Logger::logWarn("Unable to update process: " + process.first);
                return false;
            }
            if (process.second->get_ready_to_arm().ready_to_arm == false) {
                readyToArmFlag = false;
            }
        }
        m_readyToArm.ready_to_arm = readyToArmFlag;
        return true;
    }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> DepthCameraPipelineSubsystem::getDiagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> allDiagnostics;
        for (auto& process : m_pipeline) {
            auto diagnostics = process.second->getDiagnostics();
            allDiagnostics.insert(allDiagnostics.end(), diagnostics.begin(), diagnostics.end());
        }
        return allDiagnostics;
    }

}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem