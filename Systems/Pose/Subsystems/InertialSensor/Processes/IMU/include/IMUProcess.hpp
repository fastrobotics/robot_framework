/**
 * @file IMUProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-BasicHeader v0.1
 */
#pragma once

#include <BaseIMUProcess.hpp>

namespace fast::rf::PoseSystem::InertialSensorSubsystem::IMU {
    /**
     * @brief Minimal Implementation for a IMU Process
     *
     */
    class IMUProcess : public BaseIMUProcess {
       public:
        IMUProcess() : BaseIMUProcess() {}

        /**
         * @brief  Initialize the Object
         *
         * @param imu_config
         * @return true
         * @return false
         */
        bool init(IMUConfig imu_config) override;

        /**
         * @brief Update with recent timing data
         *
         * @param current_time_sec
         * @return true If update executed ok
         * @return false If update executed with some error
         */
        bool update(double current_time_sec) override;

        /**
         * @brief Human readable status of object
         *
         * @return std::string
         */
        std::string pretty() override;

        /**
         * @brief Get the imu data object
         *
         * @param data
         * @return true If New
         * @return false
         */
        bool get_imu_data(fast::rf::messages::SensorMsgs::ImuMsg& data) override;

        /**
         * @brief Get the magnetic data object
         *
         * @param data
         * @return true If New
         * @return false
         */
        bool get_magnetic_data(fast::rf::messages::SensorMsgs::MagneticFieldMsg& data) override;

       private:
    };
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem::IMU
