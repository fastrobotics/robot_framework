/**
 * @file IMUSYDTM151Driver.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-23
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <termios.h>  // Contains POSIX terminal control definitions

#include <IMUDriver/BaseIMUDriver.hpp>

#include "EasyObjectDictionary.h"
#include "EasyProfile.h"

namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    /**
     * @brief Driver for IMU Sensor SYD TM151

     * Refer to
     https://github.com/fastrobotics/component_database/blob/master/Components/Electrical/Sensors/Inertial/InertialSensors.md#sensor-robotshop-tm151
     *
     */
    class IMUSYDTM151Driver : public BaseIMUDriver {
       public:
        /**
         * @brief SensorData structure
         *
         */
        struct SensorData {
            fast::rf::messages::SensorMsgs::ImuMsg imu_msg;
            fast::rf::messages::SensorMsgs::MagneticFieldMsg magnetic_field_msg;
        };
        /**
         * @brief DataPacket structure
         *
         */
        struct DataPacket {
            bool ok;
            bool skipped;
            double acc_x_g;
            double acc_y_g;
            double acc_z_g;
            double gyro_x_rps;
            double gyro_y_rps;
            double gyro_z_rps;
            double mag_x;
            double mag_y;
            double mag_z;
            double pitch_rad;
            double roll_rad;
            double yaw_rad;
            double heading_rad;
            DataPacket() : ok(false), skipped(false) {}
        };
        static const std::string serial_port;  //!< Serial Port Name.  Defined in cpp file.
        static const int baud_rate = B115200;  //!< Baud Rate for Device
        /**
         * @brief Initialize the device
         *
         * @return true
         * @return false
         */
        bool init();
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
        DataPacket parse(char* msg, int numBytesRead);

        /**
         * @brief Convert a Data Packet to IMU Data
         *
         * @param packet
         * @return fast::rf::messages::SensorMsgs::ImuMsg
         */
        static SensorData convert(DataPacket packet);

       private:
        int serial_fd{-1};  //!< Serial Port Device
        char readBuffer[64];
        uint64_t packet_rx_ok_counter{0};
        uint64_t packet_rx_dropped_counter{0};
        EasyObjectDictionary eOD;
        EasyProfile* eP{nullptr};
    };
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem