#include <BaseGlobalPlannerManagerProcess.hpp>
namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem {
bool BaseGlobalPlannerManagerProcess::base_update(double current_time_sec, double delta_time_sec) {
    current_time_sec_ = current_time_sec;

    return true;
}
}  // namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem