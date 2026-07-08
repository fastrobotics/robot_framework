/**
 * @file BaseTeleopControlProcess.hpp
 * @author yDavid Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <ITeleopControlProcess.hpp>
#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>
namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem {
    /**
     * @brief Base TeleopControl Process
      @details Concrete TeleopControl Processes should derive from this
     *
     */
    class BaseTeleopControlProcess : public ITeleopControlProcess {
       public:
        /**
         * @brief Construct a new Base TeleopControl Process object
         *
         */
        BaseTeleopControlProcess()
            : diagnosticManager(fast::rf::UserInterfaceSystem::SYSTEM_ID,
                                fast::rf::UserInterfaceSystem::RemoteControlSubsystem::SUBSYSTEM_ID,
                                fast::rf::UserInterfaceSystem::RemoteControlSubsystem::PROCESS_TELEOPCONTROL_ID) {}
        /**
         * @brief Update the base object
         *
         * @param current_time_sec
         * @param delta_time_sec
         * @return true If ok
         * @return false If not ok
         */
        bool base_update(double current_time_sec,
                         double delta_time_sec);  //!< Base function to update

        /**
         * @brief Get the diagnostics object
         *
         * @return std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
         */
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() {
            return diagnosticManager.get_diagnostics();
        }

        /**
         * @brief Pretty print the Process
         *
         * @return std::string
         */
        std::string pretty() override;

       protected:
        double current_time_sec_{-1.0};  //!< Current system time
        fast::rf::core::infrastructure::DiagnosticManager
            diagnosticManager;  //!< Entity responsible for managing diagnostics.
    };
}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem