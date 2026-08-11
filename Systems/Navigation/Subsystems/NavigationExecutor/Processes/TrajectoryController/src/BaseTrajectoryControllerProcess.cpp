#include <BaseTrajectoryControllerProcess.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
    bool BaseTrajectoryControllerProcess::init() {
        if (controller_ == nullptr) {
            return false;
        }
        return true;
    }
    bool BaseTrajectoryControllerProcess::get_command(fast::rf::messages::GeometryMsgs::TwistMsg& cmd) {
        bool new_command = is_new_command;
        cmd = command_;
        is_new_command = false;
        return new_command;
    }
    void BaseTrajectoryControllerProcess::set_command(fast::rf::messages::GeometryMsgs::TwistMsg command) {
        command_ = command;
        is_new_command = true;
    }
    bool BaseTrajectoryControllerProcess::new_pose([[maybe_unused]] fast::rf::messages::GeometryMsgs::OdomMsg pose) {
        return true;
    }
    bool BaseTrajectoryControllerProcess::new_desired_command(
        [[maybe_unused]] fast::rf::messages::GeometryMsgs::TwistMsg cmd) {
        return true;
    }
    std::string BaseTrajectoryControllerProcess::pretty() {
        std::string str = "---Base Trajectory Controller Proess---\n";
        str += diagnosticManager.pretty();
        str += "Command:\n";
        str += "\tIs New: " + std::to_string(is_new_command) + "\n";
        str += "\t" + command_.pretty();
        return str;
    }
    bool BaseTrajectoryControllerProcess::update(double current_time_sec) {
        current_time_sec_ = current_time_sec;
        if (controller_ == nullptr) {
            return false;
        }
        bool status = controller_->update(current_time_sec);
        return status;
    }
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem