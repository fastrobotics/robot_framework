#include <BaseDriveExecutorProcess.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
    bool BaseDriveExecutorProcess::base_update(double current_time_sec) {
        current_time_sec_ = current_time_sec;

        return true;
    }
    std::string BaseDriveExecutorProcess::pretty() {
        std::string str = "\n---Drive Executor---\n";
        str += "\tT: " + std::to_string(current_time_sec_) + "\n";

        str += diagnosticManager.pretty();
        return str;
    }
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem