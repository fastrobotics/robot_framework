#include <BasicInertialSensorFuserProcess/BasicInertialSensorFuserProcess.hpp>
namespace fast::rf::PoseSystem::LocalPoseSubsystem::InertialSensorFuser {

    bool BasicInertialSensorFuserProcess::init(uint8_t imu_count) {
        bool status = BaseInertialSensorFuserProcess::init(imu_count);
        if (status == false) {
            return false;
        }
        // Only 1 IMU is supported in this
        if (imu_count > 1) {
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
    bool BasicInertialSensorFuserProcess::update(double current_time_sec) {
        bool status = BaseInertialSensorFuserProcess::update(current_time_sec);
        // GCOV_EXCL_START
        // No practical need for this
        if (status == false) {
            return false;
        }
        // GCOV_EXCL_STOP
        return true;
    }
    std::string BasicInertialSensorFuserProcess::pretty() {
        std::string str = "---Basic InertialSensorFuser Process---";
        str += BaseInertialSensorFuserProcess::pretty();
        return str;
    }
    bool BasicInertialSensorFuserProcess::new_imu_data(uint8_t imu_index,
                                                       fast::rf::messages::SensorMsgs::ImuMsg imu_data) {
        if (imu_index > imu_count_) {
            return false;
        }
        imu_rx_count++;
        diagnosticManager.update_diagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::NOERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Receiving IMU Data");
        // This is a pass-thru
        new_machine_inertial_data(imu_data);
        return true;
    }

}  // namespace fast::rf::PoseSystem::LocalPoseSubsystem::InertialSensorFuser