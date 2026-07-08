#include <BasicTeleopControlProcess/BasicTeleopControlProcess.hpp>
namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem {

    bool BasicTeleopControlProcess::init() {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        // Add more as needed
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
    bool BasicTeleopControlProcess::update([[maybe_unused]] double current_time_sec,
                                           [[maybe_unused]] double delta_time_sec) {
        bool status = BaseTeleopControlProcess::base_update(current_time_sec, delta_time_sec);
        if (status == false) {
            return false;
        }
        return true;
    }

}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem