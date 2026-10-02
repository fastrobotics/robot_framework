/**
 * @compare_tag Process-Source v0.1
 *
 */
#include <SensorInputHandlerProcess.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorInputHandler {
    fast::rf::messages::SensorMsgs::PointCloudMsg SensorInputHandlerProcess::newPointCloud(
        fast::rf::messages::SensorMsgs::PointCloudMsg msg) {
        fast::rf::messages::SensorMsgs::PointCloudMsg convertedCloud;
        convertedCloud = msg;
        return convertedCloud;
    }
    bool SensorInputHandlerProcess::init() {
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
    bool SensorInputHandlerProcess::update(double currentTimeSec) {
        bool status = BaseSensorInputHandlerProcess::update(currentTimeSec);
        if (status == false) {
            return false;
        }
        return true;
    }
    std::string SensorInputHandlerProcess::pretty() {
        std::string str = "--- SensorInputHandler Process---";
        str += BaseSensorInputHandlerProcess::pretty();
        return str;
    }

}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorInputHandler
