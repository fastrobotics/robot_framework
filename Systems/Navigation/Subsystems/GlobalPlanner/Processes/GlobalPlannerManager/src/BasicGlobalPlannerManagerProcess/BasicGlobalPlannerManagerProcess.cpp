#include <BasicGlobalPlannerManagerProcess/BasicGlobalPlannerManagerProcess.hpp>
namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem {
    bool BasicGlobalPlannerManagerProcess::init() {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        // Add more as needed
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
    bool BasicGlobalPlannerManagerProcess::update(double current_time_sec) {
        bool status = BaseGlobalPlannerManagerProcess::base_update(current_time_sec);
        if (status == false) {
            return false;
        }
        return true;
    }

}  // namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem