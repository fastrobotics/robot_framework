#include <cstring>
#include <iostream>

// Linux & System headers
#include <errno.h>   // Error integer and strerror() function
#include <fcntl.h>   // Contains file controls like O_RDWR, O_NOCTTY
#include <unistd.h>  // write(), read(), close()

#include <IMUDriver/IMURazor9DOFDriver/IMURazor9DOFDriver.hpp>
#include <Infrastructure/Logger.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#define _USE_MATH_DEFINES
#include <cmath>
namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    const std::string IMURazor9DOFDriver::serial_port = "/dev/ttyACM0";
    bool IMURazor9DOFDriver::init() {
        bool status = BaseIMUDriver::init(IMUDevice::RAZOR9DOF_IMU);
        if (status == false) {
            return false;
        }
        /**
         * @brief Implment a more generic serial port reading class during AB#1794.
         *
         */
        // GCOV_EXCL_START
        // No practical way to unit test
        serial_fd = open(serial_port.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
        if (serial_fd < 0) {
            fast::rf::Logger::log_error("Unable to open Serial Port!  Using: " + serial_port);
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
        // GCOV_EXCL_STOP
        return true;
    }
    bool IMURazor9DOFDriver::update(double current_time_sec_) {
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
        // No practical way to unit test
        std::memset(&readBuffer, 0, sizeof(readBuffer));

        // Attempt to read data
        int numBytesRead = read(serial_fd, &readBuffer, sizeof(readBuffer) - 1);

        if (numBytesRead < 0) {
            // fast::rf::Logger::log_warn("Error Reading: " + std::string(strerror(errno)));
        } else if (numBytesRead == 0) {
            packet_rx_dropped_counter++;
        } else {
            DataPacket packet = parse(readBuffer);
            if (packet.ok == true) {
                auto sensor_data = convert(packet);
                imu_data = sensor_data.imu_msg;
                imu_data.seq = packet_rx_ok_counter;
                imu_data.time_stamp = current_time_sec;

                magnetic_data = sensor_data.magnetic_field_msg;
                magnetic_data.seq = packet_rx_ok_counter;
                magnetic_data.time_stamp = current_time_sec;
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
    std::string IMURazor9DOFDriver::pretty() {
        std::string str = "---IMU Driver: Razor9DOF---\n";
        str += BaseIMUDriver::pretty() + "\n";
        double packet_rx_rate = (double)(packet_rx_ok_counter) / ((current_time_sec - start_time));
        str += "\tRX Packets: " + std::to_string(packet_rx_ok_counter) + " Rate: " + std::to_string(packet_rx_rate) +
               " (hz)\n";
        double packet_dropped_rate = (double)(packet_rx_dropped_counter) / ((current_time_sec - start_time));
        str += "\tDropped RX Packets: " + std::to_string(packet_rx_dropped_counter) +
               " Rate: " + std::to_string(packet_dropped_rate) + " (hz)\n";
        return str;
    }
    IMURazor9DOFDriver::DataPacket IMURazor9DOFDriver::parse(const char* msg) {
        DataPacket packet;
        if (msg[0] == '$') {
            std::vector<std::string> tokens;
            boost::split(tokens, msg, boost::is_any_of("$,"));
            if (tokens.size() != 15) {
                packet.ok = false;
                return packet;
            }
            try {
                /**
                 * @todo Figure out how to consume this data (including orientation + heading) in AB#1792
                 *
                 */
                packet.acc_x_g = std::stod(tokens[2]);
                packet.acc_y_g = std::stod(tokens[3]);
                packet.acc_z_g = std::stod(tokens[4]);
                packet.gyro_x_rps = std::stod(tokens[5]) * M_PI / 180.0;
                packet.gyro_y_rps = std::stod(tokens[6]) * M_PI / 180.0;
                packet.gyro_z_rps = std::stod(tokens[7]) * M_PI / 180.0;
                packet.mag_x_T = std::stod(tokens[8]);
                packet.mag_y_T = std::stod(tokens[9]);
                packet.mag_z_T = std::stod(tokens[10]);
                packet.pitch_rad = std::stod(tokens[11]) * M_PI / 180.0;
                packet.roll_rad = std::stod(tokens[12]) * M_PI / 180.0;
                packet.yaw_rad = std::stod(tokens[13]) * M_PI / 180.0;
                packet.heading_rad = std::stod(tokens[14]) * M_PI / 180.0;
                packet.ok = true;
            } catch (const std::invalid_argument& e) {
                packet.ok = false;
            }

        } else {
            packet.ok = false;
        }
        return packet;
    }
    IMURazor9DOFDriver::SensorData IMURazor9DOFDriver::convert(IMURazor9DOFDriver::DataPacket packet) {
        IMURazor9DOFDriver::SensorData sensor_data;
        fast::rf::messages::SensorMsgs::ImuMsg imu_msg;
        imu_msg.linear_acceleration.x = packet.acc_x_g * 9.81;
        imu_msg.linear_acceleration.y = packet.acc_y_g * 9.81;
        imu_msg.linear_acceleration.z = packet.acc_z_g * 9.81;
        imu_msg.angular_velocity.x = packet.gyro_x_rps;
        imu_msg.angular_velocity.y = packet.gyro_y_rps;
        imu_msg.angular_velocity.z = packet.gyro_z_rps;
        imu_msg.orientation.pitch = packet.pitch_rad;
        imu_msg.orientation.roll = packet.roll_rad;
        imu_msg.orientation.yaw = packet.yaw_rad;

        sensor_data.imu_msg = imu_msg;

        fast::rf::messages::SensorMsgs::MagneticFieldMsg magnetic_msg;
        magnetic_msg.magnetic_field.x = packet.mag_x_T;
        magnetic_msg.magnetic_field.y = packet.mag_y_T;
        magnetic_msg.magnetic_field.z = packet.mag_z_T;

        sensor_data.magnetic_field_msg = magnetic_msg;
        return sensor_data;
    }
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem