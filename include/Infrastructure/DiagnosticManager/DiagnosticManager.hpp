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
#include <vector>
namespace fast::rf::core::infrastructure {
    class DiagnosticManager {
       public:
        DiagnosticManager(uint8_t system_id, uint8_t subsystem_id, uint8_t process_id)
            : system_id(system_id), subsystem_id(subsystem_id), process_id(process_id) {}
        virtual ~DiagnosticManager() = default;
        bool is_initialized() { return initialized; }
        bool initialize_diagnostics(std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types);
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() { return diagnostics; }
        std::string pretty();

       private:
        uint8_t system_id;
        uint8_t subsystem_id;
        uint8_t process_id;
        bool initialized{false};
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> diagnostics;
    };
}  // namespace fast::rf::core::infrastructure