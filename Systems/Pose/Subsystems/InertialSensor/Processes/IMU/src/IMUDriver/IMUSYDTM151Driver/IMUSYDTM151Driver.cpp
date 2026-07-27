#include <cstring>
#include <iostream>

// Linux & System headers
#include <errno.h>   // Error integer and strerror() function
#include <fcntl.h>   // Contains file controls like O_RDWR, O_NOCTTY
#include <unistd.h>  // write(), read(), close()

#include <IMUDriver/IMUSYDTM151Driver/IMUSYDTM151Driver.hpp>
#include <Infrastructure/Logger.hpp>
namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    const std::string IMUSYDTM151Driver::serial_port = "/dev/ttyACM0";
    bool IMUSYDTM151Driver::init() {
        bool status = BaseIMUDriver::init(IMUDevice::SYDTM151_IMU);
        if (status == false) {
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
        EasyObjectDictionary eOD;
        EasyProfile eP(&eOD);
        return true;
    }
    bool IMUSYDTM151Driver::update(double current_time_sec_) {
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
            imu_data.seq++;
            imu_data.time_stamp = current_time_sec;
            packet_rx_counter++;
            fast::rf::Logger::log_debug("RX: " + std::to_string(numBytesRead) + "-->" + std::string(readBuffer));
        }
        return true;
    }
    std::string IMUSYDTM151Driver::pretty() {
        std::string str = "---IMU Driver: SYDTM151---\n";
        str += BaseIMUDriver::pretty() + "\n";
        double packet_rx_rate = (double)(packet_rx_counter) / ((current_time_sec - start_time));
        str += "\tRX Packets: " + std::to_string(packet_rx_counter) + " Rate: " + std::to_string(packet_rx_rate) +
               " (hz)\n";
        return str;
    }
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem