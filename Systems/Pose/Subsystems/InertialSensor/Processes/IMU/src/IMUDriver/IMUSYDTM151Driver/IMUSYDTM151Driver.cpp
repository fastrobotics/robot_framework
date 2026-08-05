#include <cstring>
#include <iostream>

// Linux & System headers
#include <errno.h>   // Error integer and strerror() function
#include <fcntl.h>   // Contains file controls like O_RDWR, O_NOCTTY
#include <unistd.h>  // write(), read(), close()

#include <IMUDriver/IMUSYDTM151Driver/IMUSYDTM151Driver.hpp>
#include <Infrastructure/Logger.hpp>
#define _USE_MATH_DEFINES
#include <cmath>
namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    /**
     * @todo Make this a config item during AB#1798
     *
     */
    bool IMUSYDTM151Driver::init(std::string device_name) {
        bool status = BaseIMUDriver::init(IMUDevice::SYDTM151_IMU, device_name);
        if (status == false) {
            return false;
        }
        /**
         * @brief Implment a more generic serial port reading class during AB#1794.
         *
         */
        // GCOV_EXCL_START
        // No practical way to unit test
        serial_fd = open(device_name.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
        if (serial_fd < 0) {
            fast::rf::Logger::log_error("Unable to open Serial Port!  Using: " + device_name);
            return false;
        }
        struct termios tty;
        tcgetattr(serial_fd, &tty);
        cfsetospeed(&tty, baud_rate);
        cfsetispeed(&tty, baud_rate);
        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
        tty.c_cflag |= (CLOCAL | CREAD);
        tty.c_iflag &= ~(IXON | IXOFF | IXANY);
        tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
        tty.c_oflag &= ~OPOST;
        tcsetattr(serial_fd, TCSANOW, &tty);
        eP = new EasyProfile(&eOD);
        // GCOV_EXCL_STOP
        return true;
    }
    bool IMUSYDTM151Driver::update(double current_time_sec_) {
        bool status = BaseIMUDriver::update(current_time_sec_);
        if (status == false) {
            fast::rf::Logger::log_warn("Unable to update Driver!");
            return false;
        }
        if (serial_fd < 0) {
            fast::rf::Logger::log_error("Serial Port not Accessible!");
            return false;
        }
        // GCOV_EXCL_START
        // No Practical way to unit test
        std::memset(&readBuffer, 0, sizeof(readBuffer));

        // Attempt to read data
        int numBytesRead = read(serial_fd, &readBuffer, sizeof(readBuffer) - 1);

        if (numBytesRead < 0) {
            // fast::rf::Logger::log_warn("Error Reading: " + std::string(strerror(errno)));
        } else if (numBytesRead == 0) {
            packet_rx_dropped_counter++;
        } else {
            DataPacket packet = parse(readBuffer, numBytesRead);
            if (packet.ok == true) {
                auto sensor_data = convert(packet);
                /**
                 * @todo Assign Covariance Data during AB#1795
                 *
                 */
                {
                    fast::rf::messages::SensorMsgs::ImuMsg data;
                    data = sensor_data.imu_msg;
                    data.seq = packet_rx_ok_counter;
                    data.time_stamp = current_time_sec;
                    new_imu_data(data);
                }
                {
                    fast::rf::messages::SensorMsgs::MagneticFieldMsg data;
                    data = sensor_data.magnetic_field_msg;
                    data.seq = packet_rx_ok_counter;
                    data.time_stamp = current_time_sec;
                    new_magnetic_data(data);
                }
                packet_rx_ok_counter++;

            } else if (packet.skipped == true) {
                // Do nothing, don't care.
            } else {
                packet_rx_dropped_counter++;
            }

            fast::rf::Logger::log_debug("RX: " + std::to_string(numBytesRead) + "-->" + std::string(readBuffer));
        }
        // GCOV_EXCL_STOP
        return true;
    }
    BaseIMUDriver::DataPacket IMUSYDTM151Driver::parse(char* msg, int numBytesRead) {
        // GCOV_EXCL_START
        // No Practical way to unit test
        DataPacket packet;
        Ep_Header header;  // Then let the EasyProfile do the rest such as data assembling and checksum verification.
        if (EP_SUCC_ == eP->On_RecvPkg(msg, numBytesRead, &header)) {
            uint32 fromId = header.fromId;
            (void)fromId;
            switch (header.cmd) {  // The program will only reach this line if and only if a correct and complete
                                   // package has received.
                case EP_CMD_Raw_GYRO_ACC_MAG_: {  // Here we demonstrate a few examples on how to use the received data
                    Ep_Raw_GyroAccMag ep_Raw_GyroAccMag;
                    if (EP_SUCC_ == eOD.Read_Ep_Raw_GyroAccMag(&ep_Raw_GyroAccMag)) {
                        // Raw Data received
                        packet.packet_type = (uint8_t)header.cmd;
                        packet.acc_x_g = ep_Raw_GyroAccMag.acc[0];  // Note 1: ep_Raw_GyroAccMag is defined in the
                                                                    // EasyProfile library as a global variable
                        packet.acc_y_g = ep_Raw_GyroAccMag.acc[1];  // Note 2: for the units and meaning of each value,
                                                                    // refer to EasyObjectDictionary.h
                        packet.acc_z_g = ep_Raw_GyroAccMag.acc[2];
                        packet.gyro_x_rps = ep_Raw_GyroAccMag.gyro[0] * M_PI / 180.0;
                        packet.gyro_y_rps = ep_Raw_GyroAccMag.gyro[1] * M_PI / 180.0;
                        packet.gyro_z_rps = ep_Raw_GyroAccMag.gyro[2] * M_PI / 180.0;
                        packet.mag_x_T = ep_Raw_GyroAccMag.mag[0] * 0.00005;  // Convert to Tesla
                        packet.mag_y_T = ep_Raw_GyroAccMag.mag[1] * 0.00005;  // Convert to Tesla;
                        packet.mag_z_T = ep_Raw_GyroAccMag.mag[2] * 0.00005;  // Convert to Tesla;
                        packet.ok = true;
                    }
                } break;
                case EP_CMD_RPY_: {
                    Ep_RPY ep_RPY;
                    if (EP_SUCC_ == eOD.Read_Ep_RPY(&ep_RPY)) {
                        // Roll Pitch Yaw data received
                        packet.packet_type = (uint8_t)header.cmd;
                        packet.roll_rad =
                            ep_RPY.roll * M_PI /
                            180.0;  // Note 1, ep_RPY is defined in the EasyProfile library as a global variable
                        packet.pitch_rad = ep_RPY.pitch * M_PI / 180.0;  // Note 2, for the units and meaning of each
                                                                         // value, refer to EasyObjectDictionary.h
                        packet.yaw_rad = ep_RPY.yaw * M_PI / 180.0;
                        packet.ok = true;
                    }
                } break;
                case EP_CMD_STATUS_: {
                    packet.skipped = true;
                } break;
                default:
                    fast::rf::Logger::log_warn("Got ID: " + std::to_string(header.cmd) + " But Can't Process it.");
                    break;
            }
        }
        // GCOV_EXCL_STOP
        return packet;
    }
    BaseIMUDriver::SensorData IMUSYDTM151Driver::convert(BaseIMUDriver::DataPacket packet) {
        if (packet.packet_type == (uint8_t)EP_CMD_Raw_GYRO_ACC_MAG_) {
            sensor_data_.imu_msg.linear_acceleration.x = packet.acc_x_g * 9.81;
            sensor_data_.imu_msg.linear_acceleration.y = packet.acc_y_g * 9.81;
            sensor_data_.imu_msg.linear_acceleration.z = packet.acc_z_g * 9.81;
            sensor_data_.imu_msg.angular_velocity.x = -1.0 * packet.gyro_x_rps;
            sensor_data_.imu_msg.angular_velocity.y = packet.gyro_y_rps;
            sensor_data_.imu_msg.angular_velocity.z = packet.gyro_z_rps;

            sensor_data_.magnetic_field_msg.magnetic_field.x = packet.mag_x_T;
            sensor_data_.magnetic_field_msg.magnetic_field.y = packet.mag_y_T;
            sensor_data_.magnetic_field_msg.magnetic_field.z = packet.mag_z_T;

        } else if (packet.packet_type == (uint8_t)EP_CMD_RPY_) {
            sensor_data_.imu_msg.orientation.pitch = packet.pitch_rad;
            sensor_data_.imu_msg.orientation.roll = packet.roll_rad;
            sensor_data_.imu_msg.orientation.yaw = packet.yaw_rad + M_PI;
        }

        return sensor_data_;
    }

    std::string IMUSYDTM151Driver::pretty() {
        std::string str = "---IMU Driver: SYDTM151---\n";
        str += BaseIMUDriver::pretty() + "\n";
        double packet_rx_rate = (double)(packet_rx_ok_counter) / ((current_time_sec - start_time));
        str += "\tRX Packets: " + std::to_string(packet_rx_ok_counter) + " Rate: " + std::to_string(packet_rx_rate) +
               " (hz)\n";
        double packet_dropped_rate = (double)(packet_rx_dropped_counter) / ((current_time_sec - start_time));
        str += "\tDropped RX Packets: " + std::to_string(packet_rx_dropped_counter) +
               " Rate: " + std::to_string(packet_dropped_rate) + " (hz)\n";
        return str;
    }
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem