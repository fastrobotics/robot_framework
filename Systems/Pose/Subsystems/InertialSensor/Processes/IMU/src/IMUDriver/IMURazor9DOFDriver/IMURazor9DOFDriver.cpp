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
namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    const std::string IMURazor9DOFDriver::serial_port = "/dev/ttyACM0";
    bool IMURazor9DOFDriver::init(IMUDevice device) {
        if (device != IMUDevice::RAZOR9DOF_IMU) {
            return false;
        }
        /**
         * @brief Implment a more generic serial port reading class during AB#1794.
         *
         */
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
        return true;
    }
    bool IMURazor9DOFDriver::update(double current_time_sec_) {
        bool status = BaseIMUDriver::update(current_time_sec_);
        if (status == false) {
            fast::rf::Logger::log_warn("Unable to update Driver!");
            return false;
        }
        std::memset(&readBuffer, 0, sizeof(readBuffer));

        // Attempt to read data
        int numBytesRead = read(serial_fd, &readBuffer, sizeof(readBuffer) - 1);

        if (numBytesRead < 0) {
            // fast::rf::Logger::log_warn("Error Reading: " + std::string(strerror(errno)));
        } else if (numBytesRead == 0) {
            // Timeout reached with no new data incoming
            fast::rf::Logger::log_warn("Nothing Read");
        } else {
            DataPacket data = parse(readBuffer);
            if (data.ok == true) {
                imu_data = convert(data);
                imu_data.seq = packet_rx_ok_counter;
                imu_data.time_stamp = current_time_sec;
                packet_rx_ok_counter++;
            } else {
                fast::rf::Logger::log_warn("Unable to parse!");
                packet_rx_dropped_counter++;
            }

            fast::rf::Logger::log_debug("RX: " + std::to_string(numBytesRead) + "-->" + std::string(readBuffer));
        }
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
            if (tokens.size() != 11) {
                packet.ok = false;
                return packet;
            }
            try {
                packet.acc_x_g = std::stod(tokens[2]);
                packet.acc_y_g = std::stod(tokens[3]);
                packet.acc_z_g = std::stod(tokens[4]);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid argument: Could not convert string to double." << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Out of range: The value is too large for a double." << std::endl;
            }
            packet.ok = true;
        } else {
            packet.ok = false;
        }
        return packet;
    }
    fast::rf::messages::SensorMsgs::ImuMsg IMURazor9DOFDriver::convert(IMURazor9DOFDriver::DataPacket packet) {
        fast::rf::messages::SensorMsgs::ImuMsg imu_msg;
        imu_msg.linear_acceleration.x = packet.acc_x_g * 9.81;
        imu_msg.linear_acceleration.y = packet.acc_y_g * 9.81;
        imu_msg.linear_acceleration.z = packet.acc_z_g * 9.81;
        return imu_msg;
    }
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem