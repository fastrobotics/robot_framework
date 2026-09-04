/**
 * @compare_tag Process-BaseSource v0.1
 *
 */
#include <BaseIMUProcess.hpp>
#include <IMUDriver/IMURazor9DOFDriver/IMURazor9DOFDriver.hpp>
#include <IMUDriver/IMUSYDTM151Driver/IMUSYDTM151Driver.hpp>
#include <IMUDriver/MockIMUDriver.hpp>
namespace fast::rf::PoseSystem::InertialSensorSubsystem::IMU {
    bool BaseIMUProcess::init(IMUConfig imu_config) {
        m_config = imu_config;
        bool initialized_ok = false;
        switch (m_config.imu_type) {
            case IIMUDriver::IMUDevice::MOCK_IMU:
                driver = new MockIMUDriver();
                initialized_ok = driver->init(m_config.imu_device_name);
                break;
            // GCOV_EXCL_START
            // No Practical Way to Unit Test
            case IIMUDriver::IMUDevice::RAZOR9DOF_IMU:
                driver = new IMURazor9DOFDriver();
                initialized_ok = driver->init(m_config.imu_device_name);
                break;
            case IIMUDriver::IMUDevice::SYDTM151_IMU:
                driver = new IMUSYDTM151Driver();
                initialized_ok = driver->init(m_config.imu_device_name);
                break;
            // GCOV_EXCL_STOP
            default:
                break;
        }
        if (initialized_ok == true) {
            diagnosticManager.updateDiagnostic(
                fast::rf::DiagnosticDefinition::DiagnosticType::SENSORS, fast::rf::Level::NOERROR,
                fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "IMU Initialized");
            diagnosticManager.updateDiagnostic(
                fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::NOERROR,
                fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "IMU Initialized");
            diagnosticManager.updateDiagnostic(
                fast::rf::DiagnosticDefinition::DiagnosticType::COMMUNICATIONS, fast::rf::Level::NOERROR,
                fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "IMU Initialized");
        }
        return initialized_ok;
    }
    bool BaseIMUProcess::update(double current_time_sec) {
        if (current_time_sec <= 0.0) {  // Invalid Timestamp
            fast::rf::Logger::logWarn("Invalid Timestamp!");
            return false;
        }
        current_time_sec_ = current_time_sec;
        if (driver == nullptr) {
            fast::rf::Logger::logWarn("Driver Not Initialized!");
            diagnosticManager.updateDiagnostic(
                fast::rf::DiagnosticDefinition::DiagnosticType::SENSORS, fast::rf::Level::FATAL,
                fast::rf::DiagnosticDefinition::DiagnosticMessage::DEVICE_NOT_AVAILABLE, "No IMU Initialized!");
            ready_to_arm.ready_to_arm = false;
            return false;

        } else {
            bool status = driver->update(current_time_sec_);
            if (status == false) {
                fast::rf::Logger::logWarn("Driver Not Updated!");

                diagnosticManager.updateDiagnostic(
                    fast::rf::DiagnosticDefinition::DiagnosticType::SENSORS, fast::rf::Level::ERROR,
                    fast::rf::DiagnosticDefinition::DiagnosticMessage::DIAGNOSTIC_FAILED, "Not able to Update IMU!");
            }
            double packet_dropped_rate = driver->get_packet_dropped_rate();
            if (packet_dropped_rate >= 0.0) {
                if (packet_dropped_rate > m_config.highPacketDroppedRateThreshold) {
                    diagnosticManager.updateDiagnostic(
                        fast::rf::DiagnosticDefinition::DiagnosticType::SENSORS, fast::rf::Level::ERROR,
                        fast::rf::DiagnosticDefinition::DiagnosticMessage::DROPPING_PACKETS,
                        "High Packet Drop Rate: " + std::to_string(packet_dropped_rate) + " > " +
                            std::to_string(m_config.highPacketDroppedRateThreshold) + " (Hz)");
                }
            }
            double packet_rx_rate = driver->get_packet_rx_rate();
            if (packet_rx_rate >= 0.0) {
                if (packet_rx_rate < m_config.lowPacketRxRateThreshold) {
                    diagnosticManager.updateDiagnostic(
                        fast::rf::DiagnosticDefinition::DiagnosticType::COMMUNICATIONS, fast::rf::Level::ERROR,
                        fast::rf::DiagnosticDefinition::DiagnosticMessage::DIAGNOSTIC_FAILED,
                        "Low Packet Rate: " + std::to_string(packet_rx_rate) + " < " +
                            std::to_string(m_config.lowPacketRxRateThreshold) + " (Hz)");
                }
            }
            if (diagnosticManager.getDiagnostics(fast::rf::Level::ERROR).size() == 0) {
                ready_to_arm.ready_to_arm = true;
            } else {
                ready_to_arm.ready_to_arm = false;
            }
            return true;
        }
    }
    std::string BaseIMUProcess::pretty() {
        std::string str = "\n---IMU---\n";

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
        if (driver != nullptr) {
            str += driver->pretty();
        }

        return str;
    }
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem::IMU
