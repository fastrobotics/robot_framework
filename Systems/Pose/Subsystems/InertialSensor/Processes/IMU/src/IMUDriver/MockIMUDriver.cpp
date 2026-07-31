#include <IMUDriver/MockIMUDriver.hpp>
namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    bool MockIMUDriver::init() {
        BaseIMUDriver::init(IMUDevice::MOCK_IMU);
        return true;
    }
    bool MockIMUDriver::update(double current_time_sec_) {
        BaseIMUDriver::update(current_time_sec_);
        {
            fast::rf::messages::SensorMsgs::ImuMsg data;
            get_imu_data(data);
            data.time_stamp = current_time_sec;
            data.seq++;
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
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem