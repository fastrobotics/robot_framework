#include <BaseTrajectorySelectorProcess.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectorySelector {
    bool BaseTrajectorySelectorProcess::base_update(double current_time_sec) {
        current_time_sec_ = current_time_sec;

        return true;
    }
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectorySelector