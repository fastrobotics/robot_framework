#include <BasicGlobalPathStorageProcess/BasicGlobalPathStorageProcess.hpp>
namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem::GlobalPathStorage {
    bool BasicGlobalPathStorageProcess::init() {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        // Add more as needed
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
    bool BasicGlobalPathStorageProcess::update(double current_time_sec) {
        bool status = BaseGlobalPathStorageProcess::base_update(current_time_sec);
        if (status == false) {
            return false;
        }
        return true;
    }

}  // namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem::GlobalPathStorage