#include <IMUDriver/MockIMUDriver.hpp>
namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    bool MockIMUDriver::init(IIMUDriver::IMUDevice device) {
        bool status = BaseIMUDriver::init(device);
        if (status == false) {
            return false;
        }
        /**
         * @todo Flesh this out better during AB#1732
         *
         */
        imu_data.time_stamp = 1.0;
        return true;
    }
    std::string MockIMUDriver::pretty() {
        std::string str = "---Mock IMU Driver---";
        str += BaseIMUDriver::pretty();
        return str;
    }
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem