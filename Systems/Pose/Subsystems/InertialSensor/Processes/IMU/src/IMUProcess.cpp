#include <IMUProcess.hpp>
namespace fast::rf::PoseSystem::InertialSensorSubsystem {

    bool IMUProcess::init(IMUConfig imu_config) {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SENSORS);
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::TIMING);
        diagnosticManager.initialize_diagnostics(diagnostic_types);
        bool status = BaseIMUProcess::init(imu_config);
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
    bool IMUProcess::get_imu_data(fast::rf::messages::SensorMsgs::ImuMsg& data) {
        bool status = driver->get_imu_data(data);
        data.orientation_covariance = imu_config_.orientation_covariance;
        data.angular_velocity_covariance = imu_config_.gyro_covariance;
        data.linear_acceleration_covariance = imu_config_.linear_accelerometer_covariance;

        return status;
    }

    bool IMUProcess::get_magnetic_data(fast::rf::messages::SensorMsgs::MagneticFieldMsg& data) {
        bool status = driver->get_magnetic_data(data);
        data.magnetic_field_covariance = imu_config_.magnetometer_covariance;
        return status;
    }

}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem