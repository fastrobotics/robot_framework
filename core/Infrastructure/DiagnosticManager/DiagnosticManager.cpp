#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <Infrastructure/Logger.hpp>
#include <algorithm>
namespace fast::rf::core::infrastructure {
    bool DiagnosticManager::initializeDiagnostics(
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes) {
        if ((m_systemId == 0) || (m_subsystemId == 0) || (m_processId == 0)) {
            fast::rf::Logger::logError("Can't initialize Diagnostic Manager!");
            return false;
        }
        for (auto type : diagnosticTypes) {
            fast::rf::messages::InfrastructureMsgs::DiagnosticMsg diagnostic(m_systemId, m_subsystemId, m_processId,
                                                                             type);
            m_diagnosticMap.emplace(std::pair<fast::rf::DiagnosticDefinition::DiagnosticType,
                                              fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>(type, diagnostic));
        }
        m_initialized = true;
        return true;
    }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> DiagnosticManager::getDiagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> diagnostics;
        diagnostics.reserve(m_diagnosticMap.size());
        std::transform(m_diagnosticMap.begin(), m_diagnosticMap.end(), std::back_inserter(diagnostics),
                       [](const auto& pair) { return pair.second; });
        return diagnostics;
    }
    bool DiagnosticManager::updateDiagnostic(fast::rf::DiagnosticDefinition::DiagnosticType type, fast::rf::Level level,
                                             fast::rf::DiagnosticDefinition::DiagnosticMessage message,
                                             std::string description) {
        auto it = m_diagnosticMap.find(type);
        if (it != m_diagnosticMap.end()) {
            it->second.level = level;
            it->second.diagnosticMessage = message;
            it->second.description = description;
            return true;
        }
        fast::rf::messages::InfrastructureMsgs::DiagnosticMsg diagnostic(m_systemId, m_subsystemId, m_processId, type);
        diagnostic.level = level;
        diagnostic.message = message;
        diagnostic.description = description;
        m_diagnosticMap.emplace(std::pair<fast::rf::DiagnosticDefinition::DiagnosticType,
                                          fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>(type, diagnostic));
        return true;
    }
    std::string DiagnosticManager::pretty() {
        std::string str;
        str = "---Diagnostic Manager---\n";
        uint16_t counter = 0;
        for (auto it : m_diagnosticMap) {
            str += "[" + std::to_string(counter) + "/" + std::to_string((std::size_t)m_diagnosticMap.size()) +
                   "]: " + it.second.pretty() + "\n";
            counter++;
        }
        return str;
    }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> DiagnosticManager::getDiagnostics(
        fast::rf::Level level) {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> diagnostics;
        for (auto it : m_diagnosticMap) {
            if (it.second.level >= level) {
                diagnostics.push_back(it.second);
            }
        }
        return diagnostics;
    }
}  // namespace fast::rf::core::infrastructure