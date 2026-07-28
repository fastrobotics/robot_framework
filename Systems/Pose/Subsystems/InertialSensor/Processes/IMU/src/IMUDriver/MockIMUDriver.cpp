#include <IMUDriver/MockIMUDriver.hpp>
namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    bool MockIMUDriver::init() {
        BaseIMUDriver::init(IMUDevice::MOCK_IMU);
        return true;
    }
    bool MockIMUDriver::update(double current_time_sec_) {
        BaseIMUDriver::update(current_time_sec_);
        imu_data.time_stamp = current_time_sec;
        imu_data.seq++;
        magnetic_data.time_stamp = current_time_sec;
        magnetic_data.seq++;
        return true;
    }
    std::string MockIMUDriver::pretty() {
        std::string str = "---Mock IMU Driver---\n";
        str += BaseIMUDriver::pretty();

        return str;
    }
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem