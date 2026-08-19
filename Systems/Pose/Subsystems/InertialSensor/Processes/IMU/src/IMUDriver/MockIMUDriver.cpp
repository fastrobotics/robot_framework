#include <IMUDriver/MockIMUDriver.hpp>
namespace fast::rf::PoseSystem::InertialSensorSubsystem::IMU {
    bool MockIMUDriver::init([[maybe_unused]] std::string device_name) {
        imu_device_name = "mock";
        BaseIMUDriver::init(IMUDevice::MOCK_IMU, imu_device_name);
        return true;
    }
    bool MockIMUDriver::update(double current_time_sec_) {
        BaseIMUDriver::update(current_time_sec_);
        {
            fast::rf::messages::SensorMsgs::ImuMsg data;
            get_imu_data(data);
            data.time_stamp = current_time_sec;
            data.seq++;
            data.linear_acceleration.x = 1.0;
            data.linear_acceleration.z = -9.81;
            new_imu_data(data);
        }
        {
            fast::rf::messages::SensorMsgs::MagneticFieldMsg data;
            get_magnetic_data(data);
            data.time_stamp = current_time_sec;
            data.seq++;
            new_magnetic_data(data);
        }
        return true;
    }
    std::string MockIMUDriver::pretty() {
        std::string str = "---Mock IMU Driver---\n";
        str += BaseIMUDriver::pretty();

        return str;
    }
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem::IMU