/**
 * @file BaseIMUProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <IIMUProcess.hpp>
#include <IMUDriver/IIMUDriver.hpp>
#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>
namespace fast::rf::PoseSystem::InertialSensorSubsystem::IMU {
    /**
     * @brief Base IMU Process
      @details Concrete IMU Processes should derive from this
     *
     */
    class BaseIMUProcess : public IIMUProcess {
       public:
        /**
         * @brief Construct a new Base IMU Process object
         *
         */
        BaseIMUProcess()
            : m_systemId(fast::rf::PoseSystem::SYSTEM_ID),
              m_subSystemId(fast::rf::PoseSystem::InertialSensorSubsystem::SUBSYSTEM_ID),
              m_processId(fast::rf::PoseSystem::InertialSensorSubsystem::IMU::PROCESS_IMU_ID),
              diagnosticManager(m_systemId, m_subSystemId, m_processId),
              ready_to_arm(m_systemId, m_subSystemId, m_processId) {}

        /**
         * @brief Initialize the base object.  Called by Concrete Function.
         *
         * @param imu_config
         * @return true
         * @return false
         */
        virtual bool init(IMUConfig imu_config);

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
         * @brief Pretty print the Process
         *
         * @return std::string
         */
        virtual std::string pretty();

       protected:
        uint8_t m_systemId{0};
        uint8_t m_subSystemId{0};
        uint8_t m_processId{0};
        double current_time_sec_{-1.0};  //!< Current system time
        fast::rf::core::infrastructure::DiagnosticManager
            diagnosticManager;  //!< Entity responsible for managing diagnostics.
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;  //!< Ready to Arm object
        IIMUDriver* driver{nullptr};                                               //!< IMU Driver
        IMUConfig imu_config_;                                                     //!< IMU Configuration
    };
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem::IMU