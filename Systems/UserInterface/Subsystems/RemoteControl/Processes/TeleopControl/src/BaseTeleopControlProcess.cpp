/**
 * @compare_tag Process-BaseSource v0.1
 *
 */
#include <BaseTeleopControlProcess.hpp>
#include <Infrastructure/Logger.hpp>
namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem::TeleopControl {
    bool BaseTeleopControlProcess::update(double currentTimeSec) {
        m_currentTimeSec = currentTimeSec;
        if (last_input_time_sec < 0) {
            m_diagnosticManager.updateDiagnostic(
                fast::rf::DiagnosticDefinition::DiagnosticType::REMOTE_CONTROL, fast::rf::Level::WARN,
                fast::rf::DiagnosticDefinition::DiagnosticMessage::NODATA, "Input never Received.");
        } else {
            double last_input_delta_time = currentTimeSec - last_input_time_sec;
            if (last_input_delta_time > ITeleopControlProcess::INPUT_TIMEOUT_SEC) {
                m_diagnosticManager.updateDiagnostic(
                    fast::rf::DiagnosticDefinition::DiagnosticType::REMOTE_CONTROL, fast::rf::Level::WARN,
                    fast::rf::DiagnosticDefinition::DiagnosticMessage::DROPPING_PACKETS,
                    "Have not received input for: " + std::to_string(last_input_delta_time) + " > " +
                        std::to_string(ITeleopControlProcess::INPUT_TIMEOUT_SEC) + " (sec)");
            }
        }
        auto diagnostics = m_diagnosticManager.getDiagnostics(fast::rf::Level::ERROR);
        if (diagnostics.size() == 0) {
            ready_to_arm.ready_to_arm = true;
        } else {
            for (auto diagnostic : diagnostics) {
                fast::rf::Logger::logDiagnostic(diagnostic);
            }
            ready_to_arm.ready_to_arm = false;
        }

        return true;
    }
    std::string BaseTeleopControlProcess::pretty() {
        std::string str = "";
        if (operation_mode == OperationMode::RUN) {
            str += "\nOp Mode: RUN\n";
        } else if (operation_mode == OperationMode::JOY_TEST) {
            str += "\nOp Mode: JOY TEST\n";

        } else {
            str += "\nOp Mode: UNKNOWN\n";
        }
        str += "\tSys: " + std::string(fast::rf::UserInterfaceSystem::toString(fast::rf::UserInterfaceSystem::Id{})) +
               "/" +
               std::string(fast::rf::UserInterfaceSystem::RemoteControlSubsystem::toString(
                   fast::rf::UserInterfaceSystem::RemoteControlSubsystem::Id{})) +
               "/" +
               std::string(fast::rf::UserInterfaceSystem::RemoteControlSubsystem::TeleopControl::toString(
                   fast::rf::UserInterfaceSystem::RemoteControlSubsystem::TeleopControl::Id{})) +
               "\n";
        str += "\tT: " + std::to_string(m_currentTimeSec) + "\n";
        str += "\tArm Command: " + fast::rf::pretty(robot_arm_command.armed_state) + "\n";
        str += "\tReady To Arm: " + std::to_string(ready_to_arm.ready_to_arm) + "\n";
        str += "\tDesired Twist: " + desired_twist.pretty() + "\n";
        str += m_diagnosticManager.pretty();

        return str;
    }
}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem::TeleopControl
