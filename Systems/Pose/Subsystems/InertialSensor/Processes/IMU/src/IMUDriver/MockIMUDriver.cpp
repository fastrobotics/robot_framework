#include <IMUDriver/MockIMUDriver.hpp>
namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    bool MockIMUDriver::init(IIMUDriver::IMUDevice device) {
        bool status = BaseIMUDriver::init(device);
        if (status == false) {
            return false;
        }
        return true;
    }
    bool MockIMUDriver::update(double current_time_sec_) {
        bool status = BaseIMUDriver::update(current_time_sec_);
        if (status == false) {
            return false;
        }
        imu_data.time_stamp = current_time_sec;
        imu_data.seq++;
        return true;
    }
    std::string MockIMUDriver::pretty() {
        std::string str = "---Mock IMU Driver---\n";
        str += BaseIMUDriver::pretty();

        return str;
    }
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem