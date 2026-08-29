/**
 * @file BaseLocalPoseFuserProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
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
            : diagnosticManager(fast::rf::PoseSystem::SYSTEM_ID, fast::rf::PoseSystem::LocalPoseSubsystem::SUBSYSTEM_ID,
                                fast::rf::PoseSystem::LocalPoseSubsystem::LocalPoseFuser::PROCESS_LOCALPOSEFUSER_ID),
              ready_to_arm(fast::rf::PoseSystem::SYSTEM_ID, fast::rf::PoseSystem::LocalPoseSubsystem::SUBSYSTEM_ID,
                           fast::rf::PoseSystem::LocalPoseSubsystem::LocalPoseFuser::PROCESS_LOCALPOSEFUSER_ID) {}
        /**
         * @brief Initialize the base object.  Called by Concrete Function.
         *
         * @return true
         * @return false
         */
        virtual bool init();

        /**
         * @brief Update the base object.  Called by Concrete Function.
         *
         * @param current_time_sec
         * @return true If ok
         * @return false If not ok
         */
        virtual bool update(double current_time_sec);  //!< Base function to update

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
         * @brief Pretty print the Process
         *
         * @return std::string
         */
        virtual std::string pretty();

        /**
         * @brief Handle a new computed pose data
         *
         * @param local_pose
         * @param angular_acc
         */
        void new_local_pose(fast::rf::messages::GeometryMsgs::OdomMsg local_pose,
                            fast::rf::messages::GeometryMsgs::AccelWithCovarianceMsg angular_acc);
        double current_time_sec_{-1.0};  //!< Current system time
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