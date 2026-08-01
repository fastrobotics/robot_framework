#include <IMUProcess.hpp>
namespace fast::rf::PoseSystem::InertialSensorSubsystem {

    bool IMUProcess::init(IIMUDriver::IMUDevice imu_type, std::string imu_device_name) {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SENSORS);
        diagnosticManager.initialize_diagnostics(diagnostic_types);
        bool status = BaseIMUProcess::init(imu_type, imu_device_name);
        if (status == false) {
            return false;
        }

        return status;
    }
    bool IMUProcess::update(double current_time_sec) {
        bool status = BaseIMUProcess::update(current_time_sec);
        if (status == false) {
            return false;
        }
        return true;
    }
    std::string IMUProcess::pretty() {
        std::string str = "---IMU Process---";
        str += BaseIMUProcess::pretty();
        return str;
    }
    bool IMUProcess::get_imu_data(fast::rf::messages::SensorMsgs::ImuMsg& data) { return driver->get_imu_data(data); }

    bool IMUProcess::get_magnetic_data(fast::rf::messages::SensorMsgs::MagneticFieldMsg& data) {
        return driver->get_magnetic_data(data);
    }

}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem