#include <BasicTrajectoryControllerProcess/BasicTrajectoryControllerProcess.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
    bool BasicTrajectoryControllerProcess::init() {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        // Add Others as Needed
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
    bool BasicTrajectoryControllerProcess::update(double current_time_sec) {
        bool status = BaseTrajectoryControllerProcess::update(current_time_sec);
        if (status == false) {
            return false;
        }
        return true;
    }

}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem