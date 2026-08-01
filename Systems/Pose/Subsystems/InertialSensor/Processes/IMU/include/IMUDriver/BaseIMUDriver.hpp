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
         * @brief Get the imu data object
         *
         * @param imu_data
         * @return true If new
         * @return false
         */
        bool get_imu_data(fast::rf::messages::SensorMsgs::ImuMsg& imu_data) override;

        /**
         * @brief Get the magnetic data object
         *
         * @param magnetic_data
         * @return true If new
         * @return false
         */
        bool get_magnetic_data(fast::rf::messages::SensorMsgs::MagneticFieldMsg& magnetic_data);

       protected:
        /**
         * @brief Initialize the base object.  Called by the concrete object.
         *
         * @param device
         * @param imu_device_name
         * @return true
         * @return false
         */
        virtual bool init(IIMUDriver::IMUDevice device, std::string imu_device_name);

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

        /**
         * @brief Set new IMU Data
         *
         * @param data
         */
        void new_imu_data(fast::rf::messages::SensorMsgs::ImuMsg data);

        /**
         * @brief Set new Magnetic Data
         *
         * @param data
         */
        void new_magnetic_data(fast::rf::messages::SensorMsgs::MagneticFieldMsg data);

        std::string imu_device_name{""};  //!< IMU Device Name
        double start_time{-1.0};          //!< When the driver was started
        double current_time_sec{-1.0};    //!< Current Time
       private:
        bool is_new_imu_data{false};                                     // If there's new IMU data
        bool is_new_magnetic_data{false};                                // If there's new Magnetic Data
        fast::rf::messages::SensorMsgs::ImuMsg imu_data;                 //!< IMU Data
        fast::rf::messages::SensorMsgs::MagneticFieldMsg magnetic_data;  //!< Magnetic Data
    };
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem