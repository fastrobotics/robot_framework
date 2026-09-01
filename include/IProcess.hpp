/**
 * @file IProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-08-31
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <DiagnosticMsg.hpp>
#include <ReadyToArmStatusMsg.hpp>
namespace fast::rf {
    class IProcess {
       public:
        IProcess() = default;
        virtual ~IProcess() = default;
        virtual uint8_t getSystemId() = 0;
        virtual uint8_t getSubSystemId() = 0;
        virtual uint8_t getProcessId() = 0;
        /**
         * @brief Get the diagnostic object
         *
         * @return fast::rf::messages::InfrastructureMsgs::DiagnosticMsg
         */
        virtual std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() = 0;
        virtual bool updateDiagnostic(fast::rf::DiagnosticDefinition::DiagnosticType type, fast::rf::Level level,
                                      fast::rf::DiagnosticDefinition::DiagnosticMessage message,
                                      std::string description) = 0;
        virtual fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() = 0;
        virtual bool update(double current_time_sec) = 0;
        virtual std::string pretty() = 0;
    };
}  // namespace fast::rf