#include <BasicGlobalPlannerManagerProcess/BasicGlobalPlannerManagerProcess.hpp>
namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem {
bool BasicGlobalPlannerManagerProcess::update(double current_time_sec, [[maybe_unused]] double delta_time_sec) {
    bool status = BaseGlobalPlannerManagerProcess::base_update(current_time_sec, delta_time_sec);
    if (status == false) {
        return false;
    }
    return true;
}

}  // namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem