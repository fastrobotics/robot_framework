/**
 * @compare_tag Process-Source v0.1
 *
 */
#include <SensorHealthMonitorProcess.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorHealthMonitor {
    bool SensorHealthMonitorProcess::newPointCloudMsg(std::string name,
                                                      fast::rf::messages::SensorMsgs::PointCloudMsg msg) {
        bool status = newSignalRx(name, msg.time_stamp);
        return status;
    }
    bool SensorHealthMonitorProcess::init() {
        bool status = BaseSensorHealthMonitorProcess::init();
        if (status == false) {
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
        diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SENSORS);
        diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::TIMING);
        status = m_diagnosticManager.initializeDiagnostics(diagnosticTypes);
        return status;
    }
    bool SensorHealthMonitorProcess::update(double currentTimeSec) {
        m_diagnosticManager.updateDiagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE,
                                             fast::rf::Level::NOERROR,
                                             fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "No Error");
        bool status = BaseSensorHealthMonitorProcess::update(currentTimeSec);
        if (status == false) {
            return false;
        }
        return true;
    }
    std::string SensorHealthMonitorProcess::pretty() {
        std::string str = "--- SensorHealthMonitor Process---";
        str += BaseSensorHealthMonitorProcess::pretty();
        return str;
    }

}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorHealthMonitor
