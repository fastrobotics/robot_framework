#include <BasicGlobalPathStorageProcess/BasicGlobalPathStorageProcess.hpp>
namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem {
bool BasicGlobalPathStorageProcess::update(double current_time_sec, double delta_time_sec) {
    bool status = BaseGlobalPathStorageProcess::base_update(current_time_sec, delta_time_sec);
    if (status == false) {
        return false;
    }
    return true;
}

}  // namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem