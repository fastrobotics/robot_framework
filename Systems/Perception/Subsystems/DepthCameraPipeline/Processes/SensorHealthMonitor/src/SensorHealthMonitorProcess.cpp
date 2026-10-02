/**
 * @compare_tag Process-Source v0.1
 *
 */
#include <SensorHealthMonitorProcess.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorHealthMonitor {

    bool SensorHealthMonitorProcess::init() {
        bool status = BaseSensorHealthMonitorProcess::init();
        if (status == false) {
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
        diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        // Add more as needed
        status = m_diagnosticManager.initializeDiagnostics(diagnosticTypes);
        return status;
    }
    bool SensorHealthMonitorProcess::update(double currentTimeSec) {
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
