#include <BaseFreeSpacePlannerProcess.hpp>
namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem::FreeSpacePlanner {
    bool BaseFreeSpacePlannerProcess::base_update(double current_time_sec) {
        current_time_sec_ = current_time_sec;

        return true;
    }
}  // namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem::FreeSpacePlanner