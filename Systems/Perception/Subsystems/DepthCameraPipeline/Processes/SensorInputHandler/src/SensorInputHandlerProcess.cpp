/**
 * @compare_tag Process-Source v0.1
 *
 */
#include <SensorInputHandlerProcess.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorInputHandler {
    fast::rf::messages::SensorMsgs::PointCloudMsg SensorInputHandlerProcess::newPointCloud(
        fast::rf::messages::SensorMsgs::PointCloudMsg msg) {
        fast::rf::messages::SensorMsgs::PointCloudMsg convertedCloud;
        if (msg.height > 1) {  // It's already an organized point cloud, nothing to do
            convertedCloud = msg;
            m_diagnosticManager.updateDiagnostic(
                fast::rf::DiagnosticDefinition::DiagnosticType::SENSORS, fast::rf::Level::INFO,
                fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Pass-Thru Organized Point Cloud");
        } else {
            m_diagnosticManager.updateDiagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::SENSORS,
                                                 fast::rf::Level::ERROR,
                                                 fast::rf::DiagnosticDefinition::DiagnosticMessage::DIAGNOSTIC_FAILED,
                                                 "Unorganized Point Clouds are not supported!");
        }
        return convertedCloud;
    }
    bool SensorInputHandlerProcess::init() {
        bool status = BaseSensorInputHandlerProcess::init();
        if (status == false) {
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
        diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SENSORS);
        status = m_diagnosticManager.initializeDiagnostics(diagnosticTypes);
        m_diagnosticManager.updateDiagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::INFO,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Sensor Input Handler Running");
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
