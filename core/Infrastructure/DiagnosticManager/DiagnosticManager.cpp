#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
namespace fast::rf::core::infrastructure {
    bool DiagnosticManager::initialize_diagnostics(
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types) {
        if ((system_id == 0) || (subsystem_id == 0) || (process_id == 0)) {
            return false;
        }
        for (auto type : diagnostic_types) {
            fast::rf::messages::InfrastructureMsgs::DiagnosticMsg diagnostic(system_id, subsystem_id, process_id, type);
            diagnostics.push_back(diagnostic);
        }
        initialized = true;
        return true;
    }
    std::string DiagnosticManager::pretty() {
        std::string str;
        str = "---Diagnostic Manager---\n";
        uint16_t counter = 0;
        for (auto diagnostic : diagnostics) {
            str += "[" + std::to_string(counter) + "/" + std::to_string((std::size_t)diagnostics.size()) +
                   "]: " + diagnostic.pretty() + "\n";
            counter++;
        }
        return str;
    }
}  // namespace fast::rf::core::infrastructure