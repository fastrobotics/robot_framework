/**
 * @compare_tag Process-BasicSource
 *
 */
#include <Infrastructure/Logger.hpp>
#include <ServoHatDriverProcess/ServoHatDriverProcess.hpp>
namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver {

    bool ServoHatDriverProcess::init() {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::REMOTE_CONTROL);
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::ACTUATORS);

        bool status = diagnosticManager.initializeDiagnostics(diagnostic_types);

#ifdef ARCHITECTURE_ARMV7L
        driver = new ServoHatDriver();
#else
        driver = new MockServoHatDriver();
#endif
        // GCOV_EXCL_START
        // MockServoHatDriver will always be ok
        if (driver->init() == false) {
            fast::rf::Logger::logError("Unable to Initialize Driver.  Exiting!");
            return 1;
        }
        // GCOV_EXCL_STOP
        diagnosticManager.updateDiagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::NOERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Servo Hat SW Ready.");
        diagnosticManager.updateDiagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::ACTUATORS, fast::rf::Level::NOERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Servo Hat Actuators Ready.");
        diagnosticManager.updateDiagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::REMOTE_CONTROL, fast::rf::Level::WARN,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING, "Waiting for R/C Commands.");
        return status;
    }
    bool ServoHatDriverProcess::update(double current_time_sec) {
        bool status = BaseHatDriverProcess::update(current_time_sec);
        // GCOV_EXCL_START
        // Always Ok
        if (status == false) {
            return false;
        }
        // GCOV_EXCL_STOP
        if (robot_arm_command.armed_state != fast::rf::ArmedState::ARMED) {
            for (uint8_t i = 0; i < ServoHatDriverProcess::MAX_CHANNEL_COUNT; ++i) {
                driver->setServoValue(i, 0);
            }
        }
        return true;
    }
    bool ServoHatDriverProcess::setServoValue(uint16_t channel, uint16_t value) {
        diagnosticManager.updateDiagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::REMOTE_CONTROL, fast::rf::Level::NOERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Receiving R/C Commands.");
        if (robot_arm_command.armed_state == fast::rf::ArmedState::ARMED) {
            return driver->setServoValue(channel, value);
        } else {
            return driver->setServoValue(channel, 0);
        }
    }
    std::string ServoHatDriverProcess::pretty() {
        std::string str = "\n---Servo Hat Driver Process---";
        str += BaseHatDriverProcess::pretty();
        str += "\n" + driver->pretty();
        return str;
    }

}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver