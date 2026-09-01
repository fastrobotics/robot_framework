/**
 * @file BaseLocalPoseFuserProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-BaseHeader v0.1
 */
#pragma once
#include <ILocalPoseFuserProcess.hpp>
#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>
namespace fast::rf::PoseSystem::LocalPoseSubsystem::LocalPoseFuser {
    /**
     * @brief Base LocalPoseFuser Process
      @details Concrete LocalPoseFuser Processes should derive from this
     *
     */
    class BaseLocalPoseFuserProcess : public ILocalPoseFuserProcess {
       public:
        /**
         * @brief Construct a new Base LocalPoseFuser Process object
         *
         */
        BaseLocalPoseFuserProcess()
            : m_systemId(fast::rf::PoseSystem::SYSTEM_ID),
              m_subSystemId(fast::rf::PoseSystem::LocalPoseSubsystem::SUBSYSTEM_ID),
              m_processId(fast::rf::PoseSystem::LocalPoseSubsystem::LocalPoseFuser::PROCESS_LOCALPOSEFUSER_ID),
              diagnosticManager(m_systemId, m_subSystemId, m_processId),
              ready_to_arm(m_systemId, m_subSystemId, m_processId) {}
        /**
         * @brief Initialize the base object.  Called by Concrete Function.
         *
         * @return true
         * @return false
         */
        virtual bool init();

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
            return diagnosticManager.getDiagnostics();
        }

        /**
         * @brief Get the ready to arm object
         *
         * @return fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg
         */
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() override { return ready_to_arm; }

        /**
         * @brief Get the local pose object
         *
         * @param local_pose
         * @param angular_acc
         * @return true If the data is new
         * @return false
         */
        bool get_local_pose(fast::rf::messages::GeometryMsgs::OdomMsg& local_pose,
                            fast::rf::messages::GeometryMsgs::AccelWithCovarianceMsg& angular_acc) override;

       protected:
        /**
         * @brief Update the base object.  Called by Concrete Function.
         *
         * @param currentTimeSec
         * @return true If ok
         * @return false If not ok
         */
        bool update(double currentTimeSec) override = 0;  //!< Base function to update
        bool updateDiagnostic(fast::rf::DiagnosticDefinition::DiagnosticType type, fast::rf::Level level,
                              fast::rf::DiagnosticDefinition::DiagnosticMessage message,
                              std::string description) override {
            return diagnosticManager.updateDiagnostic(type, level, message, description);
        }
        /**
         * @brief Pretty print the Process.  Called by concrete object.
         *
         * @return std::string
         */
        std::string pretty() override = 0;
        double getCurrentTimeSec() { return m_currentTimeSec; }

        /**
         * @brief Handle a new computed pose data
         *
         * @param local_pose
         * @param angular_acc
         */
        void new_local_pose(fast::rf::messages::GeometryMsgs::OdomMsg local_pose,
                            fast::rf::messages::GeometryMsgs::AccelWithCovarianceMsg angular_acc);

        uint8_t m_systemId{0};
        uint8_t m_subSystemId{0};
        uint8_t m_processId{0};
        double m_currentTimeSec{-1.0};  //!< Current system time
        fast::rf::core::infrastructure::DiagnosticManager
            diagnosticManager;  //!< Entity responsible for managing diagnostics.
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;  //!< Ready to Arm object
       private:
        fast::rf::messages::GeometryMsgs::OdomMsg local_pose_;  //!< Computed Local Pose
        fast::rf::messages::GeometryMsgs::AccelWithCovarianceMsg
            angular_acc_;               //!< Computed Local Pose Angular Acceleration
        bool is_new_local_pose{false};  //!< If the local pose is new or not
    };
}  // namespace fast::rf::PoseSystem::LocalPoseSubsystem::LocalPoseFuser
