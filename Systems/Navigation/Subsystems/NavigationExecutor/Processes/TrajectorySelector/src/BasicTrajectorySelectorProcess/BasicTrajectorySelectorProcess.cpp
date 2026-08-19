#include <BasicTrajectorySelectorProcess/BasicTrajectorySelectorProcess.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectorySelector {
    bool BasicTrajectorySelectorProcess::init() {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        // Add others as needed
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
    bool BasicTrajectorySelectorProcess::update(double current_time_sec) {
        bool status = BaseTrajectorySelectorProcess::base_update(current_time_sec);
        if (status == false) {
            return false;
        }
        return true;
    }

}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectorySelector