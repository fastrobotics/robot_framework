#include <Infrastructure/Logger.hpp>
#include <ServoHatDriverProcess/ServoHatDriverProcess.hpp>
namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem {

    bool ServoHatDriverProcess::init() {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::REMOTE_CONTROL);
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::ACTUATORS);

        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);

#ifdef ARCHITECTURE_ARMV7L
        driver = new ServoHatDriver();
#else
        driver = new MockServoHatDriver();
#endif
        if (driver->init() == false) {
            fast::rf::Logger::log_error("Unable to Initialize Driver.  Exiting!");
            return 1;
        }
        diagnosticManager.update_diagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::NOERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Servo Hat SW Ready.");
        diagnosticManager.update_diagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::ACTUATORS, fast::rf::Level::NOERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Servo Hat Actuators Ready.");
        diagnosticManager.update_diagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::REMOTE_CONTROL, fast::rf::Level::WARN,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING, "Waiting for R/C Commands.");
        return status;
    }
    bool ServoHatDriverProcess::update([[maybe_unused]] double current_time_sec,
                                       [[maybe_unused]] double delta_time_sec) {
        bool status = BaseHatDriverProcess::base_update(current_time_sec, delta_time_sec);
        if (status == false) {
            return false;
        }
        return true;
    }
    bool ServoHatDriverProcess::setServoValue(uint16_t channel, uint16_t value) {
        diagnosticManager.update_diagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::REMOTE_CONTROL, fast::rf::Level::NOERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Receiving R/C Commands.");
        return driver->setServoValue(channel, value);
    }
    std::string ServoHatDriverProcess::pretty() {
        std::string str = "\n---Servo Hat Driver Process---";
        str += base_pretty();
        str += "\n" + driver->pretty();
        return str;
    }

}  // namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem