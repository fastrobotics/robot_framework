#include <ArmStateCommander.hpp>
#include <Infrastructure/Logger.hpp>
namespace fast::rf::SafetySystem::ModeManagerSubsystem {
    bool ArmStateCommander::init() {
        arm_command.armed_state = fast::rf::ArmedState::DISARMED_CANNOTARM;
        return true;
    }
    std::string ArmStateCommander::pretty() {
        std::string str = "---Arm State Commander---\n";
        str += "\tRun Time: " + std::to_string(run_time) + " (sec)\n";
        str += "\tArmed State: " + fast::rf::pretty(arm_command.armed_state);
        return str;
    }

    bool ArmStateCommander::update(double current_time_sec) {
        if (first_run) {
            last_time_sec = current_time_sec;
        } else {
            double delta_time = current_time_sec - last_time_sec;
            last_time_sec = current_time_sec;
            run_time += delta_time;
        }
        return true;
    }
    bool ArmStateCommander::update_ready_to_arm(bool robot_ready_to_arm) {
        if (robot_ready_to_arm == false) {
            arm_command.armed_state = fast::rf::ArmedState::DISARMED_CANNOTARM;
            return true;
        }
        return true;
    }
    fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse
    ArmStateCommander::request_armstate_change([
        [maybe_unused]] fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvRequest request) {
        fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse response;
        response.request_approved = false;
        return response;
    }

}  // namespace fast::rf::SafetySystem::ModeManagerSubsystem