#include <IMUDriver/BaseIMUDriver.hpp>
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
    fast::rf::messages::SensorMsgs::ImuMsg BaseIMUDriver::get_imu_data() { return imu_data; }
    fast::rf::messages::SensorMsgs::MagneticFieldMsg BaseIMUDriver::get_magnetic_data() { return magnetic_data; }
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem