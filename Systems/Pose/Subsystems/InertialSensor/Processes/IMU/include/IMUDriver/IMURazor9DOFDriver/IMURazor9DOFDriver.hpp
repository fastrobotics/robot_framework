/**
 * @file IMURazor9DOFDriver.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-24
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <termios.h>  // Contains POSIX terminal control definitions

#include <IMUDriver/BaseIMUDriver.hpp>

namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    /**
     * @brief Driver for IMU Sensor Sparkfun Razor 9DOF
     * @todo Figure out units for mag readings in AB#1795

     * Refer to
    https://github.com/fastrobotics/component_database/blob/master/Components/Electrical/Sensors/Inertial/InertialSensors.md#sensor-sparkfun-9dof-razor-imu*
     */
    class IMURazor9DOFDriver : public BaseIMUDriver {
       public:
        static const int baud_rate = B115200;  //!< Baud Rate for Device
        /**
         * @brief Initialize the device
         *
         * @param device_name
         * @return true
         * @return false
         */
        bool init(std::string device_name);
        /**
         * @brief Human readable data for the driver
         *
         * @return std::string
         */
        std::string pretty() override;

        /**
         * @brief Update the object.
         *
         * @param current_time_sec
         * @return true
         * @return false
         */
        bool update(double current_time_sec) override;

        /**
         * @brief Parse a string that's received
         *
         * @param msg
         * @return DataPacket
         */
        static BaseIMUDriver::DataPacket parse(const char* msg);

        /**
         * @brief Convert a Data Packet to IMU Data
         *
         * @param packet
         * @return fast::rf::messages::SensorMsgs::ImuMsg
         */
        static BaseIMUDriver::SensorData convert(BaseIMUDriver::DataPacket packet);

       private:
        int serial_fd{-1};  //!< Serial Port Device
        char readBuffer[512];
    };
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem