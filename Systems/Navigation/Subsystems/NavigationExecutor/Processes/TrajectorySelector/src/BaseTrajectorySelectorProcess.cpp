#include <BaseTrajectorySelectorProcess.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
bool BaseTrajectorySelectorProcess::base_update(double current_time_sec, [[maybe_unused]] double delta_time_sec) {
    current_time_sec_ = current_time_sec;

    return true;
}
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem