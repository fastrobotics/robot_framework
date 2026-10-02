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
        if (m_diagnosticManager.getDiagnostics(fast::rf::Level::ERROR).size() == 0) {
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
        str += m_diagnosticManager.pretty();

        return str;
    }
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorHealthMonitor
