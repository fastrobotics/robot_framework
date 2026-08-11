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

        bool get_command(fast::rf::messages::GeometryMsgs::TwistMsg& cmd);

       protected:
        bool init() override = 0;
        /**
         * @brief Update the base object
         *
         * @param current_time_sec
         * @return true If ok
         * @return false If not ok
         */
        bool update(double current_time_sec) override = 0;  //!< Base function to update
        bool new_pose(fast::rf::messages::GeometryMsgs::OdomMsg pose) override = 0;
        bool new_desired_command(fast::rf::messages::GeometryMsgs::TwistMsg cmd) override = 0;
        double current_time_sec_{-1.0};  //!< Current system time
        fast::rf::core::infrastructure::DiagnosticManager
            diagnosticManager;  //!< Entity responsible for managing diagnostics.
        Controller::IController* controller{nullptr};

       private:
        fast::rf::messages::GeometryMsgs::TwistMsg command;
    };
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem