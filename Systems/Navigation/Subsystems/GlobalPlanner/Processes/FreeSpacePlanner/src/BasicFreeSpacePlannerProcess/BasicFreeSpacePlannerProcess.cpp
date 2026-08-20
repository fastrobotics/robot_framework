#include <BasicFreeSpacePlannerProcess/BasicFreeSpacePlannerProcess.hpp>
namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem::FreeSpacePlanner {
    bool BasicFreeSpacePlannerProcess::init() {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        // Add others as Needed
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
    bool BasicFreeSpacePlannerProcess::update(double current_time_sec) {
        bool status = BaseFreeSpacePlannerProcess::base_update(current_time_sec);
        if (status == false) {
            return false;
        }
        return true;
    }

}  // namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem::FreeSpacePlanner