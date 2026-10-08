/**
 * @compare_tag Process-BaseSource v0.1
 *
 */
#include <BaseSensorHealthMonitorProcess.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorHealthMonitor {
    bool BaseSensorHealthMonitorProcess::init() { return true; }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
    BaseSensorHealthMonitorProcess::getDiagnostics() {
        return m_diagnosticManager.getDiagnostics();
    }
    bool BaseSensorHealthMonitorProcess::update(double currentTimeSec) {
        m_currentTimeSec = currentTimeSec;

        bool signalsMonitoredOk = true;
        if (m_signalMonitors.size() == 0) {
            signalsMonitoredOk = false;
        }
        for (auto& signalMonitor : m_signalMonitors) {
            signalMonitor.second.update(currentTimeSec);
            auto status = signalMonitor.second.getStatus();
            for (auto subSignal : status.subSignalStatus) {
                m_diagnosticManager.updateDiagnostic(subSignal.second.diagnosticType, subSignal.second.level,
                                                     subSignal.second.diagnosticMessage, "Signal Health");
            }
            if (status.level >= fast::rf::Level::WARN) {
                signalsMonitoredOk = false;
            }
        }
        fast::rf::Logger::logWarn("xxx2: " + std::to_string(signalsMonitoredOk));
        if (signalsMonitoredOk == false) {
            m_readyToArm.ready_to_arm = false;
        } else if (m_diagnosticManager.getDiagnostics(fast::rf::Level::ERROR).size() == 0) {
            m_readyToArm.ready_to_arm = true;
        } else {
            m_readyToArm.ready_to_arm = false;
        }
        return true;
    }
    bool BaseSensorHealthMonitorProcess::initializeDiagnostics(
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes) {
        bool status = m_diagnosticManager.initializeDiagnostics(diagnosticTypes);
        return status;
    }
    bool BaseSensorHealthMonitorProcess::addSignalToMonitor(std::string signalName, std::string datatype,
                                                            double expectedRateHz, double rateTolerancePerc) {
        fast::rf::core::infrastructure::SignalMonitor signal(signalName, datatype, expectedRateHz, rateTolerancePerc);
        std::size_t before = m_signalMonitors.size();
        m_signalMonitors[signalName] = signal;
        std::size_t after = m_signalMonitors.size();
        if (after > before) {
            return true;
        }
        return false;
    }

    bool BaseSensorHealthMonitorProcess::newSignalRx(std::string signalName, double timestamp) {
        return m_signalMonitors[signalName].newData(timestamp);
    }
    std::string BaseSensorHealthMonitorProcess::pretty() {
        std::string str = "\n---SensorHealthMonitor---\n";
        str += "\tSys: " + std::string(fast::rf::PerceptionSystem::toString(fast::rf::PerceptionSystem::Id{})) + "/" +
               std::string(fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::toString(
                   fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::Id{})) +
               "/" +
               std::string(fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorHealthMonitor::toString(
                   fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorHealthMonitor::Id{})) +
               "\n";
        str += "\tT: " + std::to_string(m_currentTimeSec) + "\n";
        str += "\tReady To Arm: " + std::to_string(m_readyToArm.ready_to_arm) + "\n";
        str += m_diagnosticManager.pretty() + "\n";
        str += "Monitored Signals: " + std::to_string(m_signalMonitors.size()) + "\n";
        uint16_t counter = 0;
        for (auto signalMonitor : m_signalMonitors) {
            str += "[" + std::to_string(counter) + "/" + std::to_string(m_signalMonitors.size()) + "] " +
                   signalMonitor.second.pretty() + "\n";
        }

        return str;
    }
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorHealthMonitor
