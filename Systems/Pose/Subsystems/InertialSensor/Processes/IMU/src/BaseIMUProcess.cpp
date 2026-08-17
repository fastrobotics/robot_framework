#include <BaseIMUProcess.hpp>
#include <IMUDriver/IMURazor9DOFDriver/IMURazor9DOFDriver.hpp>
#include <IMUDriver/IMUSYDTM151Driver/IMUSYDTM151Driver.hpp>
#include <IMUDriver/MockIMUDriver.hpp>
#include <Infrastructure/Logger.hpp>
namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    bool BaseIMUProcess::init(IMUConfig imu_config) {
        imu_config_ = imu_config;
        bool initialized_ok = false;
        switch (imu_config_.imu_type) {
            case IIMUDriver::IMUDevice::MOCK_IMU:
                driver = new MockIMUDriver();
                initialized_ok = driver->init(imu_config_.imu_device_name);
                break;
            // GCOV_EXCL_START
            // No Practical Way to Unit Test
            case IIMUDriver::IMUDevice::RAZOR9DOF_IMU:
                driver = new IMURazor9DOFDriver();
                initialized_ok = driver->init(imu_config_.imu_device_name);
                break;
            case IIMUDriver::IMUDevice::SYDTM151_IMU:
                driver = new IMUSYDTM151Driver();
                initialized_ok = driver->init(imu_config_.imu_device_name);
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
            fast::rf::Logger::log_warn("Invalid Timestamp!");
            return false;
        }
        current_time_sec_ = current_time_sec;
        if (driver == nullptr) {
            fast::rf::Logger::log_warn("Driver Not Initialized!");
            diagnosticManager.update_diagnostic(
                fast::rf::DiagnosticDefinition::DiagnosticType::SENSORS, fast::rf::Level::FATAL,
                fast::rf::DiagnosticDefinition::DiagnosticMessage::DEVICE_NOT_AVAILABLE, "No IMU Initialized!");
            ready_to_arm.ready_to_arm = false;
            return false;

        } else {
            bool status = driver->update(current_time_sec_);
            if (status == false) {
                fast::rf::Logger::log_warn("Driver Not Updated!");
                diagnosticManager.update_diagnostic(
                    fast::rf::DiagnosticDefinition::DiagnosticType::SENSORS, fast::rf::Level::ERROR,
                    fast::rf::DiagnosticDefinition::DiagnosticMessage::DIAGNOSTIC_FAILED, "Not able to Update IMU!");
            }
            double packet_dropped_rate = driver->get_packet_dropped_rate();
            if (packet_dropped_rate >= 0.0) {
                if (packet_dropped_rate > HIGH_PACKET_DROPPED_RATE_THRESHOLD) {
                    diagnosticManager.update_diagnostic(
                        fast::rf::DiagnosticDefinition::DiagnosticType::SENSORS, fast::rf::Level::ERROR,
                        fast::rf::DiagnosticDefinition::DiagnosticMessage::DROPPING_PACKETS,
                        "High Packet Drop Rate: " + std::to_string(packet_dropped_rate) + " > " +
                            std::to_string(HIGH_PACKET_DROPPED_RATE_THRESHOLD) + " (Hz)");
                }
            }
            double packet_rx_rate = driver->get_packet_rx_rate();
            if (packet_rx_rate >= 0.0) {
                if (packet_rx_rate < LOW_PACKET_RX_RATE_THRESHOLD) {
                    diagnosticManager.update_diagnostic(
                        fast::rf::DiagnosticDefinition::DiagnosticType::SENSORS, fast::rf::Level::ERROR,
                        fast::rf::DiagnosticDefinition::DiagnosticMessage::DROPPING_PACKETS,
                        "Low Packet Rate: " + std::to_string(packet_rx_rate) + " < " +
                            std::to_string(LOW_PACKET_RX_RATE_THRESHOLD) + " (Hz)");
                }
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