#include <IMUDriver/IMUSYDTM151Driver/IMUSYDTM151Driver.hpp>

namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    bool IMUSYDTM151Driver::init(IMUDevice device) {
        if (device != IMUDevice::SYDTM151_IMU) {
            return false;
        }
        EasyObjectDictionary eOD;
        EasyProfile eP(&eOD);
        return true;
    }
    std::string IMUSYDTM151Driver::pretty() {
        std::string str = "---IMU Driver: SYDTM151---\n";
        str += BaseIMUDriver::pretty();
        return str;
    }
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem