#include <ArmedStateManagerProcess.hpp>
#include <Infrastructure/Logger.hpp>
namespace fast::rf::SafetySystem::ModeManagerSubsystem {

    bool ArmedStateManagerProcess::init() {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::COMMUNICATIONS);
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        // GCOV_EXCL_START
        // No reason to check this, diagnostics should likely always initialize ok
        if (status == false) {
            fast::rf::Logger::log_error("Unable to initialize Diagnostics.");
            return false;
        }
        // GCOV_EXCL_STOP

        // GCOV_EXCL_START
        // No reason to check this, always should be ok
        status = arm_state_commander.init();
        if (status == false) {
            fast::rf::Logger::log_error("Unable to initialize Arm State Commander.");
            return false;
        }
        // GCOV_EXCL_STOP

        /**
         * @todo Initialize in user space during AB#1767
         *
         */
        ready_to_arm_computer.add_monitor(fast::rf::BaseMachineSystem::SYSTEM_ID,
                                          fast::rf::BaseMachineSystem::BaseMachineSubsystem::SUBSYSTEM_ID,
                                          fast::rf::BaseMachineSystem::BaseMachineSubsystem::PROCESS_HATDRIVER_ID);

        ready_to_arm_computer.add_monitor(
            fast::rf::NavigationSystem::SYSTEM_ID,
            fast::rf::NavigationSystem::NavigationExecutorSubsystem::SUBSYSTEM_ID,
            fast::rf::NavigationSystem::NavigationExecutorSubsystem::PROCESS_DRIVE_EXECUTOR_ID);

        ready_to_arm_computer.add_monitor(
            fast::rf::UserInterfaceSystem::SYSTEM_ID,
            fast::rf::UserInterfaceSystem::RemoteControlSubsystem::SUBSYSTEM_ID,
            fast::rf::UserInterfaceSystem::RemoteControlSubsystem::PROCESS_TELEOPCONTROL_ID);
        ready_to_arm_computer.add_monitor(
            fast::rf::NavigationSystem::SYSTEM_ID,
            fast::rf::NavigationSystem::NavigationExecutorSubsystem::SUBSYSTEM_ID,
            fast::rf::NavigationSystem::NavigationExecutorSubsystem::PROCESS_TRAJECTORY_CONTROLLER_ID);

        ready_to_arm_computer.add_monitor(fast::rf::PoseSystem::SYSTEM_ID,
                                          fast::rf::PoseSystem::LocalPoseSubsystem::SUBSYSTEM_ID,
                                          fast::rf::PoseSystem::LocalPoseSubsystem::PROCESS_LOCALPOSEFUSER_ID);

        // GCOV_EXCL_START
        status = ready_to_arm_computer.init();
        if (status == false) {
            fast::rf::Logger::log_error("Unable to initialize Ready To Arm Computer");
            return false;
        }
        // GCOV_EXCL_STOP
        return status;
    }
    bool ArmedStateManagerProcess::update(double current_time_sec) {
        bool status = BaseArmedStateManagerProcess::update(current_time_sec);
        // GCOV_EXCL_START
        // Should always be ok
        if (status == false) {
            fast::rf::Logger::log_warn("Unable to update Base Armed State Manager Process.");
            return false;
        }
        // GCOV_EXCL_STOP

        status = ready_to_arm_computer.update(current_time_sec);
        if (status == false) {
            fast::rf::Logger::log_warn("Unable to update Ready To Arm Computer.");
            return false;
        }
        // GCOV_EXCL_START
        // Should always be ok
        status = arm_state_commander.update_ready_to_arm(ready_to_arm_computer.get_ready_to_arm());
        if (status == false) {
            fast::rf::Logger::log_warn("Unable to Update Arm State Commander with latest Ready To Arm.");
            return false;
        }
        // GCOV_EXCL_STOP
        // GCOV_EXCL_START
        // Should always be ok
        status = arm_state_commander.update(current_time_sec);
        if (status == false) {
            fast::rf::Logger::log_warn("Unable to update Arm State Commander.");
            return false;
        }
        // GCOV_EXCL_STOP
        diagnosticManager.update_diagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::NOERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "SW Updating OK");
        if (ready_to_arm_computer.is_all_signals_ever_received() == false) {
            diagnosticManager.update_diagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::COMMUNICATIONS,
                                                fast::rf::Level::WARN,
                                                fast::rf::DiagnosticDefinition::DiagnosticMessage::NODATA,
                                                "Some Ready to Arm Signals not ever received.");
        } else if (ready_to_arm_computer.is_all_signals_rate_ok() == false) {
            diagnosticManager.update_diagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::COMMUNICATIONS,
                                                fast::rf::Level::WARN,
                                                fast::rf::DiagnosticDefinition::DiagnosticMessage::DROPPING_PACKETS,
                                                "Some Ready to Arm Signals being Dropped.");
        } else {
            diagnosticManager.update_diagnostic(
                fast::rf::DiagnosticDefinition::DiagnosticType::COMMUNICATIONS, fast::rf::Level::NOERROR,
                fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "All Ready to Arm Signals being Received.");
        }
        return true;
    }
    std::string ArmedStateManagerProcess::pretty() {
        std::string str = BaseArmedStateManagerProcess::pretty();
        str += ready_to_arm_computer.pretty();
        str += arm_state_commander.pretty();
        return str;
    }
    fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse
    ArmedStateManagerProcess::request_armstate_change([
        [maybe_unused]] fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvRequest request) {
        auto response = arm_state_commander.request_armstate_change(request);
        return response;
    }
    bool ArmedStateManagerProcess::new_ReadyToArmStatus(
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg msg) {
        bool status = ready_to_arm_computer.new_ArmedStatus(msg);
        if (status == false) {
            fast::rf::Logger::log_warn("Unable to process: " + msg.pretty());
            return false;
        }
        return true;
    }

}  // namespace fast::rf::SafetySystem::ModeManagerSubsystem