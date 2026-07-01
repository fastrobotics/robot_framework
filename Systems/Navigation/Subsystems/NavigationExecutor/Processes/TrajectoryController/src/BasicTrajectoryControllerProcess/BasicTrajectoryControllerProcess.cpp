#include <BasicTrajectoryControllerProcess/BasicTrajectoryControllerProcess.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
bool BasicTrajectoryControllerProcess::update(double current_time_sec, [[maybe_unused]] double delta_time_sec) {
    bool status = BaseTrajectoryControllerProcess::base_update(current_time_sec, delta_time_sec);
    if (status == false) {
        return false;
    }
    return true;
}

}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem