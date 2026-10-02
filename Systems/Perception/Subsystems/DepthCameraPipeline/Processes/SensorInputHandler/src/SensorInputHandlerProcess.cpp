/**
 * @compare_tag Process-Source v0.1
 *
 */
#include <SensorInputHandlerProcess.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorInputHandler {
    void SensorInputHandlerProcess::newSensorPointCloud(
        [[maybe_unused]] fast::rf::messages::SensorMsgs::PointCloudMsg msg) {
        m_pointCloudRxCount++;
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
        str += " Rx Count: " + std::to_string(m_pointCloudRxCount);
        return str;
    }

}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorInputHandler
