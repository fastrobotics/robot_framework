/**
 * @compare_tag Process-BaseSource v0.1
 *
 */
#include <BaseDriveExecutorProcess.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::DriveExecutor {
    bool BaseDriveExecutorProcess::update(double currentTimeSec) {
        m_currentTimeSec = currentTimeSec;
        if (diagnosticManager.getDiagnostics(fast::rf::Level::ERROR).size() == 0) {
            ready_to_arm.ready_to_arm = true;
        } else {
            ready_to_arm.ready_to_arm = false;
        }
        return true;
    }
    std::string BaseDriveExecutorProcess::pretty() {
        std::string str = "\n---Drive Executor---\n";
        str += "\tSys: " + std::string(fast::rf::NavigationSystem::toString(fast::rf::NavigationSystem::Id{})) + "/" +
               std::string(fast::rf::NavigationSystem::NavigationExecutorSubsystem::toString(
                   fast::rf::NavigationSystem::NavigationExecutorSubsystem::Id{})) +
               "/" +
               std::string(fast::rf::NavigationSystem::NavigationExecutorSubsystem::DriveExecutor::toString(
                   fast::rf::NavigationSystem::NavigationExecutorSubsystem::DriveExecutor::Id{})) +
               "\n";
        str += "\tT: " + std::to_string(m_currentTimeSec) + "\n";
        str += "\tReady To Arm: " + std::to_string(ready_to_arm.ready_to_arm) + "\n";
        str += diagnosticManager.pretty();
        return str;
    }
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::DriveExecutor
