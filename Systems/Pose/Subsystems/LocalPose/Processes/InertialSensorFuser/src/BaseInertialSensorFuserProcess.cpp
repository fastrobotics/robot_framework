/**
 * @compare_tag Process-BaseSource v0.1
 *
 */
#include <BaseInertialSensorFuserProcess.hpp>
#include <mutex>
namespace fast::rf::PoseSystem::LocalPoseSubsystem::InertialSensorFuser {
    bool BaseInertialSensorFuserProcess::init(uint8_t imu_count) {
        if (imu_count == 0) {
            return false;
        }
        imu_count_ = imu_count;
        return true;
    }
    bool BaseInertialSensorFuserProcess::update([[maybe_unused]] double current_time_sec) {
        current_time_sec_ = current_time_sec;
        if (diagnosticManager.getDiagnostics(fast::rf::Level::ERROR).size() == 0) {
            ready_to_arm.ready_to_arm = true;
        } else {
            ready_to_arm.ready_to_arm = false;
        }

        return true;
    }
    std::string BaseInertialSensorFuserProcess::pretty() {
        std::string str = "\n---InertialSensorFuser---\n";
        str += "\tSys: " + std::string(fast::rf::PoseSystem::toString(fast::rf::PoseSystem::Id{})) + "/" +
               std::string(fast::rf::PoseSystem::InertialSensorSubsystem::toString(
                   fast::rf::PoseSystem::InertialSensorSubsystem::Id{})) +
               "/" +
               std::string(fast::rf::PoseSystem::InertialSensorSubsystem::IMU::toString(
                   fast::rf::PoseSystem::InertialSensorSubsystem::IMU::Id{})) +
               "\n";
        str += "\tT: " + std::to_string(current_time_sec_) + "\n";
        str += "\tReady To Arm: " + std::to_string(ready_to_arm.ready_to_arm) + "\n";
        str += diagnosticManager.pretty();
        str += "\tIMU Count: " + std::to_string(imu_count_) +
               " New Data: " + std::to_string(is_new_machine_inertial_data) + " Rx: " + std::to_string(imu_rx_count) +
               "\n";
        str += machine_inertial_data.pretty();

        return str;
    }
    void BaseInertialSensorFuserProcess::new_machine_inertial_data(fast::rf::messages::SensorMsgs::ImuMsg imu_msg) {
        static std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);
        machine_inertial_data = imu_msg;
        is_new_machine_inertial_data = true;
    }
    bool BaseInertialSensorFuserProcess::get_machine_inertial_data(fast::rf::messages::SensorMsgs::ImuMsg& imu_msg) {
        bool is_new = is_new_machine_inertial_data;
        imu_msg = machine_inertial_data;
        is_new_machine_inertial_data = false;
        return is_new;
    }
}  // namespace fast::rf::PoseSystem::LocalPoseSubsystem::InertialSensorFuser
