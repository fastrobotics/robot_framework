#include <BasicDriveExecutorProcess/BasicDriveExecutorProcess.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
    bool BasicDriveExecutorProcess::init() {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::REMOTE_CONTROL);
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::ACTUATORS);
        return initialize_diagnostics(diagnostic_types);
    }

    IDriveExecutorOutput* BasicDriveExecutorProcess::new_cmd([[maybe_unused]] GeometryMsgs::TwistMsg cmd) {
        IDriveExecutorOutput* output = nullptr;
        return output;
    }
    bool BasicDriveExecutorProcess::update(double current_time_sec, [[maybe_unused]] double delta_time_sec) {
        bool status = BaseDriveExecutorProcess::base_update(current_time_sec, delta_time_sec);
        if (status == false) {
            return false;
        }
        return true;
    }

}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem