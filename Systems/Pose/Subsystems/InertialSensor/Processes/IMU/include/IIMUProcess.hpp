/**
 * @file IIMUProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-Interface
 */
#pragma once

#include <IMUDriver/IIMUDriver.hpp>
#include <IProcess.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>
namespace fast::rf::PoseSystem::InertialSensorSubsystem::IMU {
    /**
     * @brief Interface for the IMU Process
     *
     */
    class IIMUProcess : public fast::rf::IProcess {
       public:
        static constexpr double HIGH_PACKET_DROPPED_RATE_THRESHOLD = 10.0;
        static constexpr double LOW_PACKET_RX_RATE_THRESHOLD = 50.0;
        /**
         * @brief Data structure for IMU Configuration
         *
         */
        struct IMUConfig {
            IIMUDriver::IMUDevice imu_type;  //!< The type of IMU
            std::string imu_device_name;     //!< Device File Path
            fast::rf::messages::StandardMsgs::Covariance3DMsg
                linear_accelerometer_covariance;                                        //!< Linear Acc Covariance
            fast::rf::messages::StandardMsgs::Covariance3DMsg gyro_covariance;          //!< Gyro Covariance
            fast::rf::messages::StandardMsgs::Covariance3DMsg magnetometer_covariance;  //!< Magnetometer Covariance
            fast::rf::messages::StandardMsgs::Covariance3DMsg orientation_covariance;   //!< Orientation Covariance
        };
        IIMUProcess() = default;
        virtual ~IIMUProcess() = default;

        /**
         * @brief Initialize the object
         *
         * @param imu_config
         * @return true
         * @return false
         */
        virtual bool init(IMUConfig imu_config) = 0;

        /**
         * @brief Get the imu data object
         *
         * @param data
         * @return true If the data is new
         * @return false If the data is not new
         */
        virtual bool get_imu_data(fast::rf::messages::SensorMsgs::ImuMsg& data) = 0;

        /**
         * @brief Get the magnetic data object
         *
         * @param data
         * @return true  If the data is new
         * @return false If the data is not new
         */
        virtual bool get_magnetic_data(fast::rf::messages::SensorMsgs::MagneticFieldMsg& data) = 0;
    };
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem::IMU
