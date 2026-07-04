#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <algorithm>
namespace fast::rf::core::infrastructure {
    bool DiagnosticManager::initialize_diagnostics(
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types) {
        if ((system_id == 0) || (subsystem_id == 0) || (process_id == 0)) {
            return false;
        }
        for (auto type : diagnostic_types) {
            fast::rf::messages::InfrastructureMsgs::DiagnosticMsg diagnostic(system_id, subsystem_id, process_id, type);
            diagnostic_map.emplace(std::pair<fast::rf::DiagnosticDefinition::DiagnosticType,
                                             fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>(type, diagnostic));
        }
        initialized = true;
        return true;
    }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> DiagnosticManager::get_diagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> diagnostics_;
        diagnostics_.reserve(diagnostic_map.size());
        std::transform(diagnostic_map.begin(), diagnostic_map.end(), std::back_inserter(diagnostics_),
                       [](const auto& pair) { return pair.second; });
        return diagnostics_;
    }
    bool DiagnosticManager::update_diagnostic(fast::rf::DiagnosticDefinition::DiagnosticType type,
                                              fast::rf::Level level,
                                              fast::rf::DiagnosticDefinition::DiagnosticMessage message,
                                              std::string description) {
        auto it = diagnostic_map.find(type);
        if (it != diagnostic_map.end()) {
            it->second.level = level;
            it->second.diagnosticMessage = message;
            it->second.description = description;
            return true;
        }
        return false;
    }
    std::string DiagnosticManager::pretty() {
        std::string str;
        str = "---Diagnostic Manager---\n";
        uint16_t counter = 0;
        for (auto it : diagnostic_map) {
            str += "[" + std::to_string(counter) + "/" + std::to_string((std::size_t)diagnostic_map.size()) +
                   "]: " + it.second.pretty() + "\n";
            counter++;
        }
        return str;
    }
}  // namespace fast::rf::core::infrastructure