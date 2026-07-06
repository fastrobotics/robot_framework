#include <BaseDriveExecutorProcess.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
    bool BaseDriveExecutorProcess::base_update(double current_time_sec, [[maybe_unused]] double delta_time_sec) {
        current_time_sec_ = current_time_sec;

        return true;
    }
    std::string BaseDriveExecutorProcess::pretty() {
        std::string str = diagnosticManager.pretty();
        return str;
    }
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem