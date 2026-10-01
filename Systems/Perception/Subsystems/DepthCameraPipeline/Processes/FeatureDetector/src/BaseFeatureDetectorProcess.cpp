/**
 * @compare_tag Process-BaseSource v0.1
 *
 */
#include <BaseFeatureDetectorProcess.hpp>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector {
    bool BaseFeatureDetectorProcess::init() { return true; }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> BaseFeatureDetectorProcess::getDiagnostics() {
        return m_diagnosticManager.getDiagnostics();
    }
    bool BaseFeatureDetectorProcess::update(double currentTimeSec) {
        m_currentTimeSec = currentTimeSec;
        if (m_diagnosticManager.getDiagnostics(fast::rf::Level::ERROR).size() == 0) {
            m_readyToArm.ready_to_arm = true;
        } else {
            m_readyToArm.ready_to_arm = false;
        }

        return true;
    }
    bool BaseFeatureDetectorProcess::initializeDiagnostics(
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes) {
        bool status = m_diagnosticManager.initializeDiagnostics(diagnosticTypes);
        return status;
    }
    std::string BaseFeatureDetectorProcess::pretty() {
        std::string str = "\n---FeatureDetector---\n";
        str += "\tSys: " + std::string(fast::rf::PerceptionSystem::toString(fast::rf::PerceptionSystem::Id{})) + "/" +
               std::string(fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::toString(
                   fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::Id{})) +
               "/" +
               std::string(fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector::toString(
                   fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector::Id{})) +
               "\n";
        str += "\tT: " + std::to_string(m_currentTimeSec) + "\n";
        str += "\tReady To Arm: " + std::to_string(m_readyToArm.ready_to_arm) + "\n";
        str += m_diagnosticManager.pretty();

        return str;
    }
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector
