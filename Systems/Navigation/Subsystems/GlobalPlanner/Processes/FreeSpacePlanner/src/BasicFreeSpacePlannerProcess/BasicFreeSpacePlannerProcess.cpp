#include <BasicFreeSpacePlannerProcess/BasicFreeSpacePlannerProcess.hpp>
namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem {
bool BasicFreeSpacePlannerProcess::update(double current_time_sec,
                                    double delta_time_sec) {
  bool status = BaseFreeSpacePlannerProcess::base_update(current_time_sec, delta_time_sec);
  if (status == false) {
    return false;
  }
  return true;
}

} // namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem