/**
 * @file DiagnosticManager.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-02
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <DiagnosticMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <cstdint>
#include <map>
#include <vector>
namespace fast::rf::core::infrastructure {
    /**
     * @brief A Class to manage Diagnostics
     *
     */
    class DiagnosticManager {
       public:
        /**
         * @brief Construct a new Diagnostic Manager object
         *
         * @param system_id
         * @param subsystem_id
         * @param process_id
         */
        DiagnosticManager(uint8_t system_id, uint8_t subsystem_id, uint8_t process_id)
            : system_id(system_id), subsystem_id(subsystem_id), process_id(process_id) {}

        /**
         * @brief Destroy the Diagnostic Manager object
         *
         */
        virtual ~DiagnosticManager() = default;
        /**
         * @brief Check if initialized
         *
         * @return true
         * @return false
         */
        bool is_initialized() { return initialized; }

        /**
         * @brief Initialize a Diagnostic
         * @details All diagnostics will be initialized to an "INITIALIZING" state.
         *
         * @param diagnostic_types
         * @return true
         * @return false
         */
        bool initialize_diagnostics(std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types);

        /**
         * @brief Update a diagnostic
         *
         * @param type The Diagnostic type
         * @param level The level of the Diagnostic
         * @param message The specific diagnostic message
         * @param description Human readable text describing the diagnostic
         * @return true
         * @return false
         */
        bool update_diagnostic(fast::rf::DiagnosticDefinition::DiagnosticType type, fast::rf::Level level,
                               fast::rf::DiagnosticDefinition::DiagnosticMessage message, std::string description);

        /**
         * @brief Get the diagnostics object
         *
         * @return std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
         */
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics();

        /**
         * @brief Get the text of the Diagnostic Manager in a human readable string
         *
         * @return std::string
         */
        std::string pretty();

       private:
        uint8_t system_id;
        uint8_t subsystem_id;
        uint8_t process_id;
        bool initialized{false};
        std::map<fast::rf::DiagnosticDefinition::DiagnosticType, fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
            diagnostic_map;
    };
}  // namespace fast::rf::core::infrastructure