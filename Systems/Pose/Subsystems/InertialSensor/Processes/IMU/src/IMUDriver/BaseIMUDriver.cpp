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
        return true;
    }
    std::string BaseIMUDriver::pretty() {
        std::string str = imu_data.pretty();
        return str;
    }
    fast::rf::messages::SensorMsgs::ImuMsg BaseIMUDriver::get_imu_data() { return imu_data; }
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem