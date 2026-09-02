/**
 * @compare_tag Process-BaseSource v0.1
 *
 */
#include <BaseTrajectorySelectorProcess.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectorySelector {
    bool BaseTrajectorySelectorProcess::update(double currentTimeSec) {
        m_currentTimeSec = currentTimeSec;
        if (m_diagnosticManager.getDiagnostics(fast::rf::Level::ERROR).size() == 0) {
            m_readyToArm.ready_to_arm = true;
        } else {
            m_readyToArm.ready_to_arm = false;
        }

        return true;
    }
    bool BaseTrajectorySelectorProcess::initializeDiagnostics(
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes) {
        bool status = m_diagnosticManager.initializeDiagnostics(diagnosticTypes);
        return status;
    }
    std::string BaseTrajectorySelectorProcess::pretty() {
        std::string str = "\n---BaseTrajectorySelectorProcess---\n";
        str += "\tSys: " + std::string(fast::rf::NavigationSystem::toString(fast::rf::NavigationSystem::Id{})) + "/" +
               std::string(fast::rf::NavigationSystem::NavigationExecutorSubsystem::toString(
                   fast::rf::NavigationSystem::NavigationExecutorSubsystem::Id{})) +
               "/" +
               std::string(fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectorySelector::toString(
                   fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectorySelector::Id{})) +
               "\n";
        str += "\tT: " + std::to_string(m_currentTimeSec) + "\n";
        str += "\tReady To Arm: " + std::to_string(m_readyToArm.ready_to_arm) + "\n";
        str += m_diagnosticManager.pretty();

        return str;
    }
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectorySelector
