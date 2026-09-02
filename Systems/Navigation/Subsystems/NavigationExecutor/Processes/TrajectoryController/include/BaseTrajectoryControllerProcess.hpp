/**
 * @file BaseTrajectoryControllerProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-BaseHeader v0.1
 */
#pragma once
#include <Controller/IController.hpp>
#include <ITrajectoryControllerProcess.hpp>
#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <RobotFrameworkDefinitions.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectoryController {
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
            : m_systemId(fast::rf::NavigationSystem::SYSTEM_ID),
              m_subSystemId(fast::rf::NavigationSystem::NavigationExecutorSubsystem::SUBSYSTEM_ID),
              m_processId(fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectoryController::
                              PROCESS_TRAJECTORY_CONTROLLER_ID),
              m_diagnosticManager(m_systemId, m_subSystemId, m_processId),
              ready_to_arm(m_systemId, m_subSystemId, m_processId) {}

        /**
         * @brief Get the System Id object
         *
         * @return uint8_t
         */
        uint8_t getSystemId() override { return m_systemId; }
        /**
         * @brief Get the Sub System Id object
         *
         * @return uint8_t
         */
        uint8_t getSubSystemId() override { return m_subSystemId; }
        /**
         * @brief Get the Process Id object
         *
         * @return uint8_t
         */
        uint8_t getProcessId() override { return m_processId; }
        /**
         * @brief Get the diagnostics object
         *
         * @return std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
         */
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() {
            return m_diagnosticManager.getDiagnostics();
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
         * @param currentTimeSec
         * @return true If ok
         * @return false If not ok
         */
        bool update(double currentTimeSec) override = 0;

        bool updateDiagnostic(fast::rf::DiagnosticDefinition::DiagnosticType type, fast::rf::Level level,
                              fast::rf::DiagnosticDefinition::DiagnosticMessage message,
                              std::string description) override {
            return m_diagnosticManager.updateDiagnostic(type, level, message, description);
        }

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
        uint8_t m_systemId{0};
        uint8_t m_subSystemId{0};
        uint8_t m_processId{0};
        double m_currentTimeSec{-1.0};  //!< Current system time
        fast::rf::core::infrastructure::DiagnosticManager
            m_diagnosticManager;  //!< Entity responsible for managing diagnostics.
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;  //!< Ready to Arm object
        Controller::IController* controller_{nullptr};                             //!< Interface to controller

        fast::rf::messages::GeometryMsgs::TwistMsg latest_desired_command;  //!< Storage for latest desired command

       private:
        bool is_new_command{false};

        fast::rf::messages::GeometryMsgs::TwistMsg command_;
    };
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectoryController
