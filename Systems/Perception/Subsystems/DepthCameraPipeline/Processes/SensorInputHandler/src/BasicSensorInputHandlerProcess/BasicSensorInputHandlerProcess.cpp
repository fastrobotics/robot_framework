/**
 * @compare_tag Process-BasicSource v0.1
 *
 */
#include <BasicSensorInputHandlerProcess/BasicSensorInputHandlerProcess.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorInputHandler {

    bool BasicSensorInputHandlerProcess::init() {
        bool status = BaseSensorInputHandlerProcess::init();
        if (status == false) {
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
        diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        // Add more as needed
        status = m_diagnosticManager.initializeDiagnostics(diagnosticTypes);
        return status;
    }
    bool BasicSensorInputHandlerProcess::update(double currentTimeSec) {
        bool status = BaseSensorInputHandlerProcess::update(currentTimeSec);
        if (status == false) {
            return false;
        }
        return true;
    }
    std::string BasicSensorInputHandlerProcess::pretty() {
        std::string str = "---Basic SensorInputHandler Process---";
        str += BaseSensorInputHandlerProcess::pretty();
        return str;
    }

}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorInputHandler
