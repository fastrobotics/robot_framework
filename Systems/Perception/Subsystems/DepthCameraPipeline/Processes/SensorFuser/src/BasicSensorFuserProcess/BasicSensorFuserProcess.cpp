/**
 * @compare_tag Process-BasicSource v0.1
 *
 */
#include <BasicSensorFuserProcess/BasicSensorFuserProcess.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {

    bool BasicSensorFuserProcess::init() {
        bool status = BaseSensorFuserProcess::init();
        if (status == false) {
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
        diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        // Add more as needed
        status = m_diagnosticManager.initializeDiagnostics(diagnosticTypes);
        return status;
    }
    bool BasicSensorFuserProcess::update(double currentTimeSec) {
        bool status = BaseSensorFuserProcess::update(currentTimeSec);
        if (status == false) {
            return false;
        }
        return true;
    }
    std::string BasicSensorFuserProcess::pretty() {
        std::string str = "---Basic SensorFuser Process---";
        str += BaseSensorFuserProcess::pretty();
        return str;
    }

}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser
