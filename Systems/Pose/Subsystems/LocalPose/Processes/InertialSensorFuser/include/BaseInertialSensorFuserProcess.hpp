/**
 * @file BaseInertialSensorFuserProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-BaseHeader v0.1
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
            : m_systemId(fast::rf::PoseSystem::SYSTEM_ID),
              m_subSystemId(fast::rf::PoseSystem::LocalPoseSubsystem::SUBSYSTEM_ID),
              m_processId(
                  fast::rf::PoseSystem::LocalPoseSubsystem::InertialSensorFuser::PROCESS_INERTIALSENSORFUSER_ID),
              diagnosticManager(m_systemId, m_subSystemId, m_processId),
              ready_to_arm(m_systemId, m_subSystemId, m_processId) {}
        /**
         * @brief Initialize the base object.  Called by Concrete Function.
         *
         * @param imu_count
         * @return true
         * @return false
         */
        virtual bool init(uint8_t imu_count);

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
        bool updateDiagnostic(fast::rf::DiagnosticDefinition::DiagnosticType type, fast::rf::Level level,
                              fast::rf::DiagnosticDefinition::DiagnosticMessage message,
                              std::string description) override {
            return diagnosticManager.updateDiagnostic(type, level, message, description);
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
        uint8_t m_systemId{0};
        uint8_t m_subSystemId{0};
        uint8_t m_processId{0};
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
