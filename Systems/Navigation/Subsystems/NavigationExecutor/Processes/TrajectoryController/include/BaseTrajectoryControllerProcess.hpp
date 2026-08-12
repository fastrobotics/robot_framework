/**
 * @file BaseTrajectoryControllerProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <Controller/IController.hpp>
#include <ITrajectoryControllerProcess.hpp>
#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <RobotFrameworkDefinitions.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
    /**
     * @brief Base TrajectoryController Process
      @details Concrete TrajectoryController Processes should derive from this
     *
     */
    class BaseTrajectoryControllerProcess : public ITrajectoryControllerProcess {
       public:
        /**
         * @brief Construct a new Base TrajectoryController Process object
         *
         */
        BaseTrajectoryControllerProcess()
            : diagnosticManager(
                  fast::rf::NavigationSystem::SYSTEM_ID,
                  fast::rf::NavigationSystem::NavigationExecutorSubsystem::SUBSYSTEM_ID,
                  fast::rf::NavigationSystem::NavigationExecutorSubsystem::PROCESS_TRAJECTORY_CONTROLLER_ID) {}

        /**
         * @brief Get the diagnostics object
         *
         * @return std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
         */
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() {
            return diagnosticManager.get_diagnostics();
        }

        /**
         * @brief Get the ready to arm object
         *
         * @return fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg
         */
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() override { return ready_to_arm; }
        /**
         * @brief Get the command data
         *
         * @param cmd
         * @return true If the command is new
         * @return false If the command is not new
         */
        bool get_command(fast::rf::messages::GeometryMsgs::TwistMsg& cmd);

       protected:
        /**
         * @brief Initialize the class.  Called by concrete class.
         *
         * @return true
         * @return false
         */
        bool init() override = 0;

        /**
         * @brief Human readable string
         *
         * @return std::string
         */
        std::string pretty() override = 0;

        /**
         * @brief Update the base object
         *
         * @param current_time_sec
         * @return true If ok
         * @return false If not ok
         */
        bool update(double current_time_sec) override = 0;

        /**
         * @brief Process a pose
         *
         * @param pose
         * @return true
         * @return false
         */
        bool new_pose(fast::rf::messages::GeometryMsgs::OdomMsg pose) override = 0;

        /**
         * @brief Process a new desired command
         *
         * @param cmd
         * @return true
         * @return false
         */
        bool new_desired_command(fast::rf::messages::GeometryMsgs::TwistMsg cmd) override = 0;

        /**
         * @brief Set the command data
         *
         * @param command
         */
        void set_command(fast::rf::messages::GeometryMsgs::TwistMsg command);

        double current_time_sec_{-1.0};  //!< Current system time
        fast::rf::core::infrastructure::DiagnosticManager
            diagnosticManager;  //!< Entity responsible for managing diagnostics.
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;  //!< Ready to Arm object
        Controller::IController* controller_{nullptr};                             //!< Interface to controller

        fast::rf::messages::GeometryMsgs::TwistMsg latest_desired_command;  //!< Storage for latest desired command

       private:
        bool is_new_command{false};

        fast::rf::messages::GeometryMsgs::TwistMsg command_;
    };
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem