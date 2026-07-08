/**
 * @file ITeleopControlProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <DiagnosticMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <TwistMsg.hpp>
#include <vector>

namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem {
    /**
     * @brief Define Key Pressed Enum
     *
     */
    enum class KeyPressed {
        UNKNOWN = 0,      //!< Unknown Key
        UP_ARROW = 1,     //!< Up Arrow
        DOWN_ARROW = 2,   //!< Down Arrow
        LEFT_ARROW = 3,   //!< Left Arrow
        RIGHT_ARROW = 4,  //!< Right Arrow
        SPACE_BAR = 5,    //!< Space
        ESC = 6,          //!< Escape
        END_OF_LIST = 7   //!< Not supported, used for range checks
    };
    /**
     * @brief Interface for the TeleopControl Process
     *
     */
    class ITeleopControlProcess {
       public:
        ITeleopControlProcess() = default;
        virtual ~ITeleopControlProcess() = default;

        /**
         * @brief Initialize the object
         *
         * @return true
         * @return false
         */
        virtual bool init() = 0;

        /**
         * @brief Generic Update function
         *
         * @param current_time_sec Current time stamp
         * @param delta_time_sec Difference in time between previous iterations
         * @return true If the process updated ok
         * @return false If the process did not update ok
         */
        virtual bool update(double current_time_sec, double delta_time_sec) = 0;

        /**
         * @brief Pretty print the Process
         *
         * @return std::string
         */
        virtual std::string pretty() = 0;

        /**
         * @brief Get the diagnostic object
         *
         * @return fast::rf::messages::InfrastructureMsgs::DiagnosticMsg
         */
        virtual std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() = 0;

        /**
         * @brief Process a Key Pressed value
         *
         * @param key
         * @return true
         * @return false
         */
        virtual bool key_pressed(KeyPressed key) = 0;

        /**
         * @brief Get the twist output object
         *
         * @return fast::rf::messages::GeometryMsgs::TwistMsg
         */
        virtual fast::rf::messages::GeometryMsgs::TwistMsg get_twist_output() = 0;
    };
}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem