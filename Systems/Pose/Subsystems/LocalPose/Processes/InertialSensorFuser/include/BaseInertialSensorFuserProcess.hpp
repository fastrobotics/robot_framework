/**
 * @file BaseInertialSensorFuserProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <IInertialSensorFuserProcess.hpp>
#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>
namespace fast::rf::PoseSystem::LocalPoseSubsystem::InertialSensorFuser {
    /**
     * @brief Base InertialSensorFuser Process
      @details Concrete InertialSensorFuser Processes should derive from this
     *
     */
    class BaseInertialSensorFuserProcess : public IInertialSensorFuserProcess {
       public:
        /**
         * @brief Construct a new Base InertialSensorFuser Process object
         *
         */
        BaseInertialSensorFuserProcess()
            : diagnosticManager(
                  fast::rf::PoseSystem::SYSTEM_ID, fast::rf::PoseSystem::LocalPoseSubsystem::SUBSYSTEM_ID,
                  fast::rf::PoseSystem::LocalPoseSubsystem::InertialSensorFuser::PROCESS_INERTIALSENSORFUSER_ID),
              ready_to_arm(
                  fast::rf::PoseSystem::SYSTEM_ID, fast::rf::PoseSystem::LocalPoseSubsystem::SUBSYSTEM_ID,
                  fast::rf::PoseSystem::LocalPoseSubsystem::InertialSensorFuser::PROCESS_INERTIALSENSORFUSER_ID) {}
        /**
         * @brief Initialize the base object.  Called by Concrete Function.
         *
         * @param imu_count
         * @return true
         * @return false
         */
        virtual bool init(uint8_t imu_count);

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
         * @brief Get the machine inertial data object
         *
         * @param imu_msg
         * @return true If the data is new
         * @return false False if the data is old
         */
        bool get_machine_inertial_data(fast::rf::messages::SensorMsgs::ImuMsg& imu_msg);

       protected:
        /**
         * @brief Pretty print the Process
         *
         * @return std::string
         */
        virtual std::string pretty();

        /**
         * @brief Give the Fuser the latest computed machine inertial data.  Expectation is that this is called by
         * concrete class whenever a new datum is computed.
         *
         * @param imu_msg
         */
        void new_machine_inertial_data(fast::rf::messages::SensorMsgs::ImuMsg imu_msg);
        double current_time_sec_{-1.0};  //!< Current system time
        fast::rf::core::infrastructure::DiagnosticManager
            diagnosticManager;  //!< Entity responsible for managing diagnostics.
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;  //!< Ready to Arm object
        uint8_t imu_count_{0};                                                     //!< How many IMU's are to be used
        uint64_t imu_rx_count{0};  //!< How many IMU messages have been received

       private:
        bool is_new_machine_inertial_data{false};
        fast::rf::messages::SensorMsgs::ImuMsg machine_inertial_data;
    };
}  // namespace fast::rf::PoseSystem::LocalPoseSubsystem::InertialSensorFuser