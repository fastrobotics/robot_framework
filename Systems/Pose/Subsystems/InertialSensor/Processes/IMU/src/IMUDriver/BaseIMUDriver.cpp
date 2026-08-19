#include <IMUDriver/BaseIMUDriver.hpp>
#include <Infrastructure/Logger.hpp>
#include <mutex>
namespace fast::rf::PoseSystem::InertialSensorSubsystem::IMU {
    bool BaseIMUDriver::init(IIMUDriver::IMUDevice device, std::string device_name) {
        if ((device == IIMUDriver::IMUDevice::UNKNOWN) || (device == IIMUDriver::IMUDevice::END_OF_LIST)) {
            return false;
        }
        imu_device_name = device_name;
        return true;
    }
    bool BaseIMUDriver::update(double current_time_sec_) {
        current_time_sec = current_time_sec_;
        if (start_time < 0.0) {
            start_time = current_time_sec_;
        }

        if ((current_time_sec - start_time) > 5.0) {  // Allow the Process to accumulate some data
            packet_rx_rate = (double)(packet_rx_ok_counter) / ((current_time_sec - start_time));
            packet_dropped_rate = (double)(packet_rx_dropped_counter) / ((current_time_sec - start_time));
        }
        return true;
    }
    std::string BaseIMUDriver::pretty() {
        std::string str = "---Base IMU Driver: " + imu_device_name + " ---\n";
        str += "\tRX Packets: " + std::to_string(packet_rx_ok_counter) + " Rate: " + std::to_string(packet_rx_rate) +
               " (hz)\n";
        str += "\tDropped RX Packets: " + std::to_string(packet_rx_dropped_counter) +
               " Rate: " + std::to_string(packet_dropped_rate) + " (hz)\n";
        str += imu_data.pretty();
        str += magnetic_data.pretty();
        return str;
    }
    void BaseIMUDriver::new_imu_data(fast::rf::messages::SensorMsgs::ImuMsg data) {
        static std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);
        imu_data = data;
        is_new_imu_data = true;
    }

    void BaseIMUDriver::new_magnetic_data(fast::rf::messages::SensorMsgs::MagneticFieldMsg data) {
        static std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);
        magnetic_data = data;
        is_new_magnetic_data = true;
    }
    bool BaseIMUDriver::get_imu_data(fast::rf::messages::SensorMsgs::ImuMsg& data) {
        static std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);
        data = imu_data;
        bool status = is_new_imu_data;
        is_new_imu_data = false;
        return status;
    }
    bool BaseIMUDriver::get_magnetic_data(fast::rf::messages::SensorMsgs::MagneticFieldMsg& data) {
        static std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);
        data = magnetic_data;
        bool status = is_new_magnetic_data;
        is_new_magnetic_data = false;
        return status;
    }
    void BaseIMUDriver::increment_packet_rx_counter() { packet_rx_ok_counter++; }

    void BaseIMUDriver::increment_packet_rx_dropped_counter() { packet_rx_dropped_counter++; }
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem::IMU