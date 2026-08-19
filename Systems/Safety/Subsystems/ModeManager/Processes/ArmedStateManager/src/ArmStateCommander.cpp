#include <ArmStateCommander.hpp>
#include <Infrastructure/Logger.hpp>
namespace fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager {
    bool ArmStateCommander::init() {
        arm_command.armed_state = fast::rf::ArmedState::DISARMED_CANNOTARM;
        return true;
    }
    std::string ArmStateCommander::pretty() {
        std::string str = "---Arm State Commander---\n";
        str += "\tRun Time: " + std::to_string(run_time) + " (sec)\n";
        str += "\tArmed State: " + fast::rf::pretty(arm_command.armed_state);
        if (arm_command.armed_state == fast::rf::ArmedState::DISARMED_CANNOTARM) {
            str += "\tReason: Robot Reports Unable to Arm";
        }
        return str;
    }

    bool ArmStateCommander::update(double current_time_sec) {
        if (first_run) {
            last_time_sec = current_time_sec;
            first_run = false;
        } else {
            double delta_time = current_time_sec - last_time_sec;
            if (arm_command.armed_state == fast::rf::ArmedState::ARMING) {
                hold_timer += delta_time;
            } else {
                hold_timer = 0.0;
            }
            if (hold_timer >= ArmStateCommander::ARMING_HOLD_TIME) {
                arm_command.armed_state = fast::rf::ArmedState::ARMED;
                fast::rf::Logger::log_notice("Changing Armed State to: " + fast::rf::pretty(arm_command.armed_state));
            }
            last_time_sec = current_time_sec;
            run_time += delta_time;
        }
        return true;
    }
    bool ArmStateCommander::update_ready_to_arm(bool robot_ready_to_arm) {
        if (robot_ready_to_arm == false) {
            auto prev_state = arm_command.armed_state;
            arm_command.armed_state = fast::rf::ArmedState::DISARMED_CANNOTARM;
            if (prev_state != arm_command.armed_state) {
                fast::rf::Logger::log_warn("Changing Armed State to: " + fast::rf::pretty(arm_command.armed_state));
            }
        } else {
            if (arm_command.armed_state == fast::rf::ArmedState::DISARMED_CANNOTARM) {
                arm_command.armed_state = fast::rf::ArmedState::DISARMED;
                fast::rf::Logger::log_notice("Changing Armed State to: " + fast::rf::pretty(arm_command.armed_state));
            }
        }
        return true;
    }
    fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse
    ArmStateCommander::request_armstate_change(
        fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvRequest request) {
        fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse response;
        response.current_armed_state = arm_command.armed_state;

        if (request.requested_armed_state == fast::rf::ArmedState::ARMED) {
            if (arm_command.armed_state == fast::rf::ArmedState::DISARMED) {
                arm_command.armed_state = fast::rf::ArmedState::ARMING;
                fast::rf::Logger::log_notice("Changing Armed State to: " + fast::rf::pretty(arm_command.armed_state));
                response.current_armed_state = arm_command.armed_state;

                response.request_approved = true;
                return response;
            }
        } else if (request.requested_armed_state == fast::rf::ArmedState::DISARMED) {
            if ((arm_command.armed_state == fast::rf::ArmedState::ARMED) ||
                (arm_command.armed_state == fast::rf::ArmedState::ARMING)) {
                arm_command.armed_state = fast::rf::ArmedState::DISARMED;
                fast::rf::Logger::log_notice("Changing Armed State to: " + fast::rf::pretty(arm_command.armed_state));
                response.current_armed_state = arm_command.armed_state;
                response.request_approved = true;
                return response;
            }
        }
        fast::rf::Logger::log_warn("Unable to Approve Arm Request");
        fast::rf::Logger::log_warn(pretty());
        response.request_approved = false;
        return response;
    }

}  // namespace fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager