#include <BaseTrajectoryControllerProcess.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
    bool BaseTrajectoryControllerProcess::init() {
        if (controller == nullptr) {
            return false;
        }
        return true;
    }
    bool BaseTrajectoryControllerProcess::get_command(
        [[maybe_unused]] fast::rf::messages::GeometryMsgs::TwistMsg& cmd) {
        return false;
    }
    bool BaseTrajectoryControllerProcess::new_pose([[maybe_unused]] fast::rf::messages::GeometryMsgs::OdomMsg pose) {
        return false;
    }
    bool BaseTrajectoryControllerProcess::new_desired_command(
        [[maybe_unused]] fast::rf::messages::GeometryMsgs::TwistMsg cmd) {
        return false;
    }
    bool BaseTrajectoryControllerProcess::update(double current_time_sec) {
        current_time_sec_ = current_time_sec;
        bool status = controller->update(current_time_sec);
        return status;
    }
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem