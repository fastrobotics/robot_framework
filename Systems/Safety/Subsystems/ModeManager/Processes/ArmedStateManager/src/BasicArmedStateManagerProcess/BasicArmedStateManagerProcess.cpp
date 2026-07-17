#include <BasicArmedStateManagerProcess/BasicArmedStateManagerProcess.hpp>
namespace fast::rf::SafetySystem::ModeManagerSubsystem {

    bool BasicArmedStateManagerProcess::init() {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        /**
         * @todo Implement this during AB#1766
         */
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
    bool BasicArmedStateManagerProcess::update([[maybe_unused]] double current_time_sec,
                                               [[maybe_unused]] double delta_time_sec) {
        bool status = BaseArmedStateManagerProcess::base_update(current_time_sec, delta_time_sec);
        if (status == false) {
            return false;
        }
        return true;
    }

}  // namespace fast::rf::SafetySystem::ModeManagerSubsystem