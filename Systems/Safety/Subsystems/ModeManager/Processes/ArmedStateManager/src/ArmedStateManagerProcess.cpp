#include <ArmedStateManagerProcess.hpp>
namespace fast::rf::SafetySystem::ModeManagerSubsystem {

    bool ArmedStateManagerProcess::init() {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::COMMUNICATIONS);
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);

        if (status == false) {
            return false;
        }
        status = arm_state_commander.init();
        if (status == false) {
            return false;
        }
        /**
         * @todo Initialize in user space during AB#1767
         *
         */
        ready_to_arm_computer.add_monitor(fast::rf::BaseMachineSystem::SYSTEM_ID,
                                          fast::rf::BaseMachineSystem::BaseMachineSubsystem::SUBSYSTEM_ID,
                                          fast::rf::BaseMachineSystem::BaseMachineSubsystem::PROCESS_HATDRIVER_ID);

        status = ready_to_arm_computer.init();
        if (status == false) {
            return false;
        }
        return status;
    }
    bool ArmedStateManagerProcess::update([[maybe_unused]] double current_time_sec,
                                          [[maybe_unused]] double delta_time_sec) {
        bool status = BaseArmedStateManagerProcess::base_update(current_time_sec, delta_time_sec);
        if (status == false) {
            return false;
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
        [maybe_unused]] fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse request) {
        fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse response;
        return response;
    }
    bool ArmedStateManagerProcess::new_ReadyToArmStatus([
        [maybe_unused]] fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg msg) {
        return false;
    }

}  // namespace fast::rf::SafetySystem::ModeManagerSubsystem