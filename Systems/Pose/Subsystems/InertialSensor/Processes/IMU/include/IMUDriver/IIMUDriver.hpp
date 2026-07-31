/**
 * @file IIMUDriver.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-23
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <ImuMsg.hpp>
#include <MagneticFieldMsg.hpp>
#include <string>
namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    /**
     * @brief Interface for an IMU Driver
     *
     */
    class IIMUDriver {
       public:
        /**
         * @brief Define all supported IMU's
         *
         */
        enum class IMUDevice {
            UNKNOWN = 0,   //!< Unknown IMU
            MOCK_IMU = 1,  //!< Mock, used for interface testing
            SYDTM151_IMU =
                2,  //!< Sensor:
                    //!< https://github.com/fastrobotics/component_database/blob/master/Components/Electrical/Sensors/Inertial/InertialSensors.md#sensor-robotshop-tm151
            RAZOR9DOF_IMU = 3,
            END_OF_LIST = 4  //!< Last item of list. Used for Range Checks.
        };
        /**
         * @brief Convert a IMU name to a type
         *
         * @param name
         * @return IMUDevice
         */
        static IMUDevice convert_name(std::string name) {
            if (name == "MOCK") {
                return IMUDevice::MOCK_IMU;
            } else if (name == "SYDTM151") {
                return IMUDevice::SYDTM151_IMU;
            } else if (name == "RAZOR9DOF") {
                return IMUDevice::RAZOR9DOF_IMU;
            } else {
                return IMUDevice::UNKNOWN;
            }
        }
        IIMUDriver() = default;
        virtual ~IIMUDriver() = default;
        /**
         * @brief Initialize the driver
         *
         * @return true
         * @return false
         */
        virtual bool init() = 0;
        /**
         * @brief Human readable string
         *
         * @return std::string
         */
        virtual std::string pretty() = 0;

        /**
         * @brief Get the imu data object
         *
         * @param imu_data
         * @return true if New
         * @return false
         */
        virtual bool get_imu_data(fast::rf::messages::SensorMsgs::ImuMsg& imu_data) = 0;

        /**
         * @brief Get the magnetic data object
         *
         * @param data
         * @return true If New
         * @return false
         */
        virtual bool get_magnetic_data(fast::rf::messages::SensorMsgs::MagneticFieldMsg& data) = 0;

        /**
         * @brief Update the driver
         *
         * @param current_time_sec
         * @return true
         * @return false
         */
        virtual bool update(double current_time_sec) = 0;
    };
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem