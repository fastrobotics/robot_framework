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
        struct Monitor {
            uint8_t systemID;
            uint8_t subsystemID;
            uint8_t componentID;
            using MonitorKey = std::tuple<uint8_t, uint8_t, uint8_t>;
            MonitorKey key;
            bool ready_to_arm;
            double last_update_time_sec;

            Monitor(uint8_t systemID, uint8_t subsystemID, uint8_t componentID)
                : systemID(systemID),
                  subsystemID(subsystemID),
                  componentID(componentID),
                  ready_to_arm(false),
                  last_update_time_sec(-1.0) {
                key = std::make_tuple(systemID, subsystemID, componentID);
            }
        };
        /**
         * @brief Add Monitor
         *
         * @param systemID
         * @param subystemID
         * @param componentID
         * @return true
         * @return false
         */
        bool add_monitor(uint8_t systemID, uint8_t subystemID, uint8_t componentID);
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
        bool ready_to_arm{false};
        std::map<Monitor::MonitorKey, Monitor> monitors;
    };
}  // namespace fast::rf::SafetySystem::ModeManagerSubsystem