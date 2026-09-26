/**
 * @compare_tag Process-BaseSource v0.1
 *
 */
#include <BaseDepthCameraFeatureHandlerProcess.hpp>
namespace fast::rf::PerceptionSystem::ObjectTrackerSubsystem::DepthCameraFeatureHandler {
    bool BaseDepthCameraFeatureHandlerProcess::init() { return true; }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
    BaseDepthCameraFeatureHandlerProcess::getDiagnostics() {
        return m_diagnosticManager.getDiagnostics();
    }
    bool BaseDepthCameraFeatureHandlerProcess::update(double currentTimeSec) {
        m_currentTimeSec = currentTimeSec;
        if (m_diagnosticManager.getDiagnostics(fast::rf::Level::ERROR).size() == 0) {
            m_readyToArm.ready_to_arm = true;
        } else {
            m_readyToArm.ready_to_arm = false;
        }

        return true;
    }
    bool BaseDepthCameraFeatureHandlerProcess::initializeDiagnostics(
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes) {
        bool status = m_diagnosticManager.initializeDiagnostics(diagnosticTypes);
        return status;
    }
    std::string BaseDepthCameraFeatureHandlerProcess::pretty() {
        std::string str = "\n---DepthCameraFeatureHandler---\n";
        str += "\tSys: " + std::string(fast::rf::PerceptionSystem::toString(fast::rf::PerceptionSystem::Id{})) + "/" +
               std::string(fast::rf::PerceptionSystem::ObjectTrackerSubsystem::toString(
                   fast::rf::PerceptionSystem::ObjectTrackerSubsystem::Id{})) +
               "/" +
               std::string(fast::rf::PerceptionSystem::ObjectTrackerSubsystem::DepthCameraFeatureHandler::toString(
                   fast::rf::PerceptionSystem::ObjectTrackerSubsystem::DepthCameraFeatureHandler::Id{})) +
               "\n";
        str += "\tT: " + std::to_string(m_currentTimeSec) + "\n";
        str += "\tReady To Arm: " + std::to_string(m_readyToArm.ready_to_arm) + "\n";
        str += m_diagnosticManager.pretty();

        return str;
    }
}  // namespace fast::rf::PerceptionSystem::ObjectTrackerSubsystem::DepthCameraFeatureHandler
