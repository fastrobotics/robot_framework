/**
 * @file IInertialSensorFuserProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-Interface
 */
#pragma once
#include <DiagnosticMsg.hpp>
#include <IProcess.hpp>
#include <ImuMsg.hpp>
#include <ReadyToArmStatusMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>

namespace fast::rf::PoseSystem::LocalPoseSubsystem::InertialSensorFuser {
    /**
     * @brief Interface for the InertialSensorFuser Process
     *
     */
    class IInertialSensorFuserProcess : public fast::rf::IProcess {
       public:
        IInertialSensorFuserProcess() = default;
        virtual ~IInertialSensorFuserProcess() = default;

        /**
         * @brief Initialize the object
         *
         * @param imu_count How many IMU's are there
         * @return true
         * @return false
         */
        virtual bool init(uint8_t imu_count) = 0;

        /**
         * @brief Process a new IMU Message
         *
         * @param imu_index
         * @param imu_data
         * @return true
         * @return false
         */
        virtual bool new_imu_data(uint8_t imu_index, fast::rf::messages::SensorMsgs::ImuMsg imu_data) = 0;

        /**
         * @brief Get the machine inertial data object
         *
         * @param imu_msg
         * @return true
         * @return false
         */
        virtual bool get_machine_inertial_data(fast::rf::messages::SensorMsgs::ImuMsg& imu_msg) = 0;
    };
}  // namespace fast::rf::PoseSystem::LocalPoseSubsystem::InertialSensorFuser