/**
 * @file BaseIMUDriver.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-23
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <IMUDriver/IIMUDriver.hpp>
#include <ImuMsg.hpp>
namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    /**
     * @brief Base IMU Driver
     *
     */
    class BaseIMUDriver : public IIMUDriver {
       public:
        /**
         * @brief SensorData structure
         *
         */
        struct SensorData {
            fast::rf::messages::SensorMsgs::ImuMsg imu_msg;                       //!< IMU Sensor Data
            fast::rf::messages::SensorMsgs::MagneticFieldMsg magnetic_field_msg;  //!< Magnetic Sensor Data
        };
        /**
         * @brief DataPacket structure
         *
         */
        struct DataPacket {
            bool ok;             //!< If the packet was parsed ok
            bool skipped;        //!< If the packet was skipped
            double acc_x_g;      //!< Acceleration in G's
            double acc_y_g;      //!< Acceleration in G's
            double acc_z_g;      //!< Acceleration in G's
            double gyro_x_rps;   //!< Rotation Rate in rad/s
            double gyro_y_rps;   //!< Rotation Rate in rad/s
            double gyro_z_rps;   //!< Rotation Rate in rad/s
            double mag_x_T;      //!< Magnetometer reading in Tesla
            double mag_y_T;      //!< Magnetometer reading in Tesla
            double mag_z_T;      //!< Magnetometer reading in Tesla
            double pitch_rad;    //!< Orientation in Radians
            double roll_rad;     //!< Orientation in Radians
            double yaw_rad;      //!< Orientation in Radians
            double heading_rad;  //!< Heading in Radians
            DataPacket() : ok(false), skipped(false) {}
        };
        /**
         * @brief Get the imu data
         *
         * @return fast::rf::messages::SensorMsgs::ImuMsg
         */
        fast::rf::messages::SensorMsgs::ImuMsg get_imu_data() override;

        /**
         * @brief Get the magnetic data
         *
         * @return fast::rf::messages::SensorMsgs::MagneticFieldMsg
         */
        fast::rf::messages::SensorMsgs::MagneticFieldMsg get_magnetic_data();

       protected:
        /**
         * @brief Initialize the base object.  Called by the concrete object.
         *
         * @param device
         * @return true
         * @return false
         */
        virtual bool init(IIMUDriver::IMUDevice device);

        /**
         * @brief Get a human readable string of the object.  Called by the concrete object.
         *
         * @return std::string
         */
        virtual std::string pretty();

        /**
         * @brief Update the base object.  Called by the concrete object.
         *
         * @param current_time_sec
         * @return true
         * @return false
         */
        virtual bool update(double current_time_sec);

        fast::rf::messages::SensorMsgs::ImuMsg imu_data;                 //!< IMU Data
        fast::rf::messages::SensorMsgs::MagneticFieldMsg magnetic_data;  //!< Magnetic Data
        double start_time{-1.0};                                         //!< When the driver was started
        double current_time_sec{-1.0};                                   //!< Current Time
    };
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem