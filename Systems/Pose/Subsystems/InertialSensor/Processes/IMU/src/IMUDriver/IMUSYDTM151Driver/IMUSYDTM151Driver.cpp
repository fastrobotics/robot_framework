#include <IMUDriver/IMUSYDTM151Driver/IMUSYDTM151Driver.hpp>
#include <Infrastructure/Logger.hpp>
namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    const std::string IMUSYDTM151Driver::serial_port = "/dev/ttyUSB0";
    bool IMUSYDTM151Driver::init(IMUDevice device) {
        if (device != IMUDevice::SYDTM151_IMU) {
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
        fast::rf::Logger::log_warn("Implement this!!!");
        return false;
    }
    std::string IMUSYDTM151Driver::pretty() {
        std::string str = "---IMU Driver: SYDTM151---\n";
        str += BaseIMUDriver::pretty();
        return str;
    }
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem