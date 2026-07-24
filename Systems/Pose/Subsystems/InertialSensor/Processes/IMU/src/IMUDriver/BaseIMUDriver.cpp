#include <IMUDriver/BaseIMUDriver.hpp>
namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    bool BaseIMUDriver::init(IIMUDriver::IMUDevice device) {
        if ((device == IIMUDriver::IMUDevice::UNKNOWN) || (device == IIMUDriver::IMUDevice::END_OF_LIST)) {
            return false;
        }
        return true;
    }
    std::string BaseIMUDriver::pretty() {
        std::string str = "";
        return str;
    }
    fast::rf::messages::SensorMsgs::ImuMsg BaseIMUDriver::get_imu_data() { return imu_data; }
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem