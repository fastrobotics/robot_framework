#include <BaseDriveExecutorProcess.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
    bool BaseDriveExecutorProcess::initialize_diagnostics(
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types) {
        if (diagnostic_types.size() == 0) {
            return false;
        }
        for (auto diagnostic_type : diagnostic_types) {
            auto diagnostic = root_diagnostic;
            diagnostic.diagnosticType = (uint8_t)diagnostic_type;
            diagnostics.push_back(diagnostic);
        }
        if (diagnostic_types.size() == diagnostics.size()) {
            return true;
        }
        return false;
    }
    bool BaseDriveExecutorProcess::base_update(double current_time_sec, [[maybe_unused]] double delta_time_sec) {
        current_time_sec_ = current_time_sec;

        return true;
    }
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem