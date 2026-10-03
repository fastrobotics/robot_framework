/**
 * @file SignalMonitor.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-10-02
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <RobotFrameworkDefinitions.hpp>
#include <cstdint>
#include <map>
#include <string>
namespace fast::rf::core::infrastructure {
    /**
     * @brief Monitors health of a signal
     *
     */
    class SignalMonitor {
       public:
        struct SubSignalStatus {
            SubSignalStatus() = default;
            SubSignalStatus(fast::rf::DiagnosticDefinition::DiagnosticType diagnosticType)
                : diagnosticType(diagnosticType) {}
            fast::rf::DiagnosticDefinition::DiagnosticType diagnosticType{
                fast::rf::DiagnosticDefinition::DiagnosticType::UNKNOWN_TYPE};
            fast::rf::Level level{fast::rf::Level::UNKNOWN};

            fast::rf::DiagnosticDefinition::DiagnosticMessage diagnosticMessage{
                fast::rf::DiagnosticDefinition::DiagnosticMessage::UNKNOWN};
        };
        /**
         * @brief Signal Status represents the state of the Signal
         *
         */
        struct SignalStatus {
            fast::rf::Level level{fast::rf::Level::UNKNOWN};
            std::map<fast::rf::DiagnosticDefinition::DiagnosticType, SubSignalStatus> subSignalStatus;
            std::string pretty() {
                std::string str = "Level: " + fast::rf::pretty(level);
                return str;
            }
        };
        static constexpr uint16_t INITIAL_SAMPLES_TO_ACCUMULATE =
            10;  //!< How many samples to collect before making a determination if the signal is ok or not.
        SignalMonitor(std::string signalName, std::string dataType, double expectedRateHz)
            : m_signalName(signalName), m_dataType(dataType), m_expectedRateHz(expectedRateHz) {
            // Initialize Sub Signal's
            {
                SubSignalStatus subSignalStatus(fast::rf::DiagnosticDefinition::DiagnosticType::SENSORS);
                m_status.subSignalStatus[subSignalStatus.diagnosticType] = subSignalStatus;
            }
            {
                SubSignalStatus subSignalStatus(fast::rf::DiagnosticDefinition::DiagnosticType::TIMING);
                m_status.subSignalStatus[subSignalStatus.diagnosticType] = subSignalStatus;
            }
        }

        /**
         * @brief
         *
         * @param timestamp
         * @todo Should use signal timestamp for other checks (i.e. non-sensical timestamp)
         * @return true
         * @return false
         */
        bool newData(double timestamp);  //!< Give the Signal Monitor new Data
        bool update(double timestamp);   //!< Periodically update the Signal Monitor
        SignalStatus getStatus() { return m_status; }
        std::string pretty();

       private:
        // Config Variables
        std::string m_signalName{""};
        std::string m_dataType{""};
        double m_expectedRateHz{-1.0};

        // Runtime Variables
        uint64_t m_rxCount{0};
        SignalStatus m_status;
        double m_startTime{-1.0};
        double m_actualRate{-1.0};
    };
}  // namespace fast::rf::core::infrastructure