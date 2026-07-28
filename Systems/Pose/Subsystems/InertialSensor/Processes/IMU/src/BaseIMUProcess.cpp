#include <BaseIMUProcess.hpp>
#include <IMUDriver/IMURazor9DOFDriver/IMURazor9DOFDriver.hpp>
#include <IMUDriver/IMUSYDTM151Driver/IMUSYDTM151Driver.hpp>
#include <IMUDriver/MockIMUDriver.hpp>
namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    bool BaseIMUProcess::init(IIMUDriver::IMUDevice imu_type) {
        bool initialized_ok = false;
        switch (imu_type) {
            case IIMUDriver::IMUDevice::MOCK_IMU:
                driver = new MockIMUDriver();
                initialized_ok = driver->init();
                break;
            // GCOV_EXCL_START
            // No Practical Way to Unit Test
            case IIMUDriver::IMUDevice::RAZOR9DOF_IMU:
                driver = new IMURazor9DOFDriver();
                initialized_ok = driver->init();
                break;
            case IIMUDriver::IMUDevice::SYDTM151_IMU:
                driver = new IMUSYDTM151Driver();
                initialized_ok = driver->init();
                break;
            // GCOV_EXCL_STOP
            default:
                break;
        }
        if (initialized_ok == true) {
            diagnosticManager.update_diagnostic(
                fast::rf::DiagnosticDefinition::DiagnosticType::SENSORS, fast::rf::Level::NOERROR,
                fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "IMU Initialized");
            diagnosticManager.update_diagnostic(
                fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::NOERROR,
                fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "IMU Initialized");
        }
        return initialized_ok;
    }
    bool BaseIMUProcess::update(double current_time_sec) {
        if (current_time_sec <= 0.0) {  // Invalid Timestamp
            return false;
        }
        current_time_sec_ = current_time_sec;
        if (driver == nullptr) {
            diagnosticManager.update_diagnostic(
                fast::rf::DiagnosticDefinition::DiagnosticType::SENSORS, fast::rf::Level::FATAL,
                fast::rf::DiagnosticDefinition::DiagnosticMessage::DEVICE_NOT_AVAILABLE, "No IMU Initialized!");
            ready_to_arm.ready_to_arm = false;
            return false;

        } else {
            bool status = driver->update(current_time_sec_);
            if (status == false) {
                diagnosticManager.update_diagnostic(
                    fast::rf::DiagnosticDefinition::DiagnosticType::SENSORS, fast::rf::Level::ERROR,
                    fast::rf::DiagnosticDefinition::DiagnosticMessage::DIAGNOSTIC_FAILED, "Not able to Update IMU!");
            }
            if (diagnosticManager.get_diagnostics(fast::rf::Level::ERROR).size() == 0) {
                ready_to_arm.ready_to_arm = true;
            } else {
                ready_to_arm.ready_to_arm = false;
            }
            return true;
        }
    }
    std::string BaseIMUProcess::pretty() {
        std::string str = "\n---IMU---\n";
        str += "\tT: " + std::to_string(current_time_sec_) + "\n";
        str += "\tReady To Arm: " + std::to_string(ready_to_arm.ready_to_arm) + "\n";
        str += diagnosticManager.pretty();
        if (driver != nullptr) {
            str += driver->pretty();
        }

        return str;
    }
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem