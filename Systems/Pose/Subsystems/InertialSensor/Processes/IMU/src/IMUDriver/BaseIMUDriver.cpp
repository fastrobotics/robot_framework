#include <IMUDriver/BaseIMUDriver.hpp>
#include <mutex>
namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    bool BaseIMUDriver::init(IIMUDriver::IMUDevice device) {
        if ((device == IIMUDriver::IMUDevice::UNKNOWN) || (device == IIMUDriver::IMUDevice::END_OF_LIST)) {
            return false;
        }
        return true;
    }
    bool BaseIMUDriver::update(double current_time_sec_) {
        current_time_sec = current_time_sec_;
        if (start_time < 0.0) {
            start_time = current_time_sec_;
        }
        return true;
    }
    std::string BaseIMUDriver::pretty() {
        std::string str = imu_data.pretty();
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
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem