/**
 * @file ReadyToArmComputer.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-17
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <ReadyToArmStatusMsg.hpp>
#include <cstdint>
#include <map>
#include <string>
#include <tuple>
namespace fast::rf::SafetySystem::ModeManagerSubsystem {
    /**
     * @brief Ready To Arm Computer
     * @details Creates multiple monitors, and as long as they all True and received frequently, Robot can be Armed.
     *
     */
    class ReadyToArmComputer {
       public:
        static constexpr double PROCESS_TIMEOUT_SEC =
            5.0;  //!< How long before not receiving a Process Update times out
        using MonitorKey = std::tuple<uint8_t, uint8_t, uint8_t>;  //!< Definition for Key
        /**
         * @brief Generate a Monitor Key
         *
         * @param systemID
         * @param subsystemID
         * @param processID
         * @return MonitorKey
         */
        static MonitorKey generate_key(uint8_t systemID, uint8_t subsystemID, uint8_t processID) {
            return std::make_tuple(systemID, subsystemID, processID);
        }
        /**
         * @brief Data Structure for encoding Monitors
         *
         */
        struct Monitor {
            uint8_t systemID;          //!< System ID
            uint8_t subsystemID;       //!< Subsystem ID
            uint8_t processID;         //!< Process ID
            MonitorKey key;            //!< Key for Monitor
            bool ready_to_arm;         //!< If the process is ready to arm
            double time_last_updated;  //!< Timestamp when the Monitor was updated.

            /**
             * @brief Construct a new Monitor object
             *
             * @param systemID
             * @param subsystemID
             * @param processID
             */
            Monitor(uint8_t systemID, uint8_t subsystemID, uint8_t processID)
                : systemID(systemID),
                  subsystemID(subsystemID),
                  processID(processID),
                  ready_to_arm(false),
                  time_last_updated(-1.0) {
                key = generate_key(systemID, subsystemID, processID);
            }
            /**
             * @brief Human readable string for Monitor
             *
             * @param after_string A user string to append after
             * @return std::string
             */
            std::string pretty(std::string after_string = "") {
                std::string str = std::to_string(systemID) + "-" + std::to_string(subsystemID) + "-" +
                                  std::to_string(processID) + " Ready To Arm: " + std::to_string(ready_to_arm) +
                                  " Time Last Update: " + std::to_string(time_last_updated) + " (sec)" + after_string;
                return str;
            }
        };
        /**
         * @brief Add Monitor
         *
         * @param systemID
         * @param subystemID
         * @param processID
         * @return true
         * @return false
         */
        bool add_monitor(uint8_t systemID, uint8_t subystemID, uint8_t processID);
        /**
         * @brief Initialize the Object.  Call this AFTER adding the monitors
         *
         * @return true
         * @return false
         */
        bool init();
        /**
         * @brief Human readable string
         *
         * @return std::string
         */
        std::string pretty();
        /**
         * @brief General Update
         *
         * @param current_time_sec
         * @return true
         * @return false
         */
        bool update(double current_time_sec);
        /**
         * @brief Get the ready to arm data for the entire Robot
         *
         * @return true
         * @return false
         */
        bool get_ready_to_arm() { return ready_to_arm; }
        /**
         * @brief Process a new Armed Status Message
         *
         * @param msg
         * @return true
         * @return false
         */
        bool new_ArmedStatus(fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg msg);

       private:
        double current_time_sec{-1.0};
        bool ready_to_arm{false};
        std::map<MonitorKey, Monitor> monitors;
    };
}  // namespace fast::rf::SafetySystem::ModeManagerSubsystem