/**
 * @compare_tag Process-BaseSource v0.1
 *
 */
#include <BaseObjectEstimatorProcess.hpp>
namespace fast::rf::PerceptionSystem::ObjectTrackerSubsystem::ObjectEstimator {
    bool BaseObjectEstimatorProcess::init() { return true; }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> BaseObjectEstimatorProcess::getDiagnostics() {
        return m_diagnosticManager.getDiagnostics();
    }
    bool BaseObjectEstimatorProcess::update(double currentTimeSec) {
        m_currentTimeSec = currentTimeSec;
        if (m_diagnosticManager.getDiagnostics(fast::rf::Level::ERROR).size() == 0) {
            m_readyToArm.ready_to_arm = true;
        } else {
            m_readyToArm.ready_to_arm = false;
        }

        return true;
    }
    bool BaseObjectEstimatorProcess::initializeDiagnostics(
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes) {
        bool status = m_diagnosticManager.initializeDiagnostics(diagnosticTypes);
        return status;
    }
    std::string BaseObjectEstimatorProcess::pretty() {
        std::string str = "\n---ObjectEstimator---\n";
        str += "\tSys: " + std::string(fast::rf::PerceptionSystem::toString(fast::rf::PerceptionSystem::Id{})) + "/" +
               std::string(fast::rf::PerceptionSystem::ObjectTrackerSubsystem::toString(
                   fast::rf::PerceptionSystem::ObjectTrackerSubsystem::Id{})) +
               "/" +
               std::string(fast::rf::PerceptionSystem::ObjectTrackerSubsystem::ObjectEstimator::toString(
                   fast::rf::PerceptionSystem::ObjectTrackerSubsystem::ObjectEstimator::Id{})) +
               "\n";
        str += "\tT: " + std::to_string(m_currentTimeSec) + "\n";
        str += "\tReady To Arm: " + std::to_string(m_readyToArm.ready_to_arm) + "\n";
        str += m_diagnosticManager.pretty();

        return str;
    }
}  // namespace fast::rf::PerceptionSystem::ObjectTrackerSubsystem::ObjectEstimator
