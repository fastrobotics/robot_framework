

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseIMUProcess.hpp>
#include <IIMUProcess.hpp>
#include <IMUProcess.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::PoseSystem::InertialSensorSubsystem;
class TestIMUProcessInterface : public IIMUProcess {
   public:
    bool init([[maybe_unused]] IMUConfig imu_config) { return true; }
    bool update([[maybe_unused]] double current_time_sec) override { return false; }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> empty;

        return empty;
    }
    std::string pretty() override { return ""; }
    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() {
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;
        return ready_to_arm;
    }
    bool get_imu_data(fast::rf::messages::SensorMsgs::ImuMsg& data) {
        fast::rf::messages::SensorMsgs::ImuMsg imu_data;
        data = imu_data;
        return true;
    }
    bool get_magnetic_data(fast::rf::messages::SensorMsgs::MagneticFieldMsg& data) {
        fast::rf::messages::SensorMsgs::MagneticFieldMsg magnetic_data;
        data = magnetic_data;
        return true;
    }
};
TEST(TestIMUProcessInterface, InterfaceTests) {
    TestIMUProcessInterface SUT;
    IIMUProcess::IMUConfig imu_config;
    imu_config.imu_type = IIMUDriver::convert_name("UNKNOWN");
    imu_config.imu_device_name = "";
    ASSERT_TRUE(SUT.init(imu_config));
    ASSERT_EQ(SUT.get_diagnostics().size(), 0);
    ASSERT_FALSE(SUT.update(0.1));
    fast::rf::messages::SensorMsgs::ImuMsg imu_data;
    ASSERT_TRUE(SUT.get_imu_data(imu_data));
    fast::rf::messages::SensorMsgs::MagneticFieldMsg magnetic_data;
    ASSERT_TRUE(SUT.get_magnetic_data(magnetic_data));
}
class TestBaseIMUProcess : public BaseIMUProcess {
   public:
    TestBaseIMUProcess() : BaseIMUProcess() {}
    bool init(IMUConfig imu_config) override {
        bool status = BaseIMUProcess::init(imu_config);
        if (status == false) {
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
    bool update(double current_time_sec) override { return BaseIMUProcess::update(current_time_sec); }
    std::string pretty() {
        std::string str = "---Test-Base---\n";
        str += BaseIMUProcess::pretty();
        return str;
    }
    bool inject_error() {
        return diagnosticManager.update_diagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::ERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::DIAGNOSTIC_FAILED, "Testing Error Injection");
    }
    bool clear_error() {
        return diagnosticManager.update_diagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::NOERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Clearing Error Injection");
    }
    bool get_imu_data(fast::rf::messages::SensorMsgs::ImuMsg& data) {
        fast::rf::messages::SensorMsgs::ImuMsg imu_data;
        data = imu_data;
        return true;
    }
    bool get_magnetic_data(fast::rf::messages::SensorMsgs::MagneticFieldMsg& data) {
        fast::rf::messages::SensorMsgs::MagneticFieldMsg magnetic_data;
        data = magnetic_data;
        return true;
    }
};
TEST(BaseIMUProcess, BasicAssertions) {
    TestBaseIMUProcess SUT;
    IIMUProcess::IMUConfig imu_config;
    imu_config.imu_type = IIMUDriver::convert_name("MOCK");
    imu_config.imu_device_name = "";
    ASSERT_TRUE(SUT.init(imu_config));
    ASSERT_GT(SUT.get_diagnostics().size(), 0);
    ASSERT_TRUE(SUT.update(0.1));
    ASSERT_TRUE(SUT.inject_error());
    ASSERT_TRUE(SUT.update(1.0));
    ASSERT_FALSE(SUT.get_ready_to_arm().ready_to_arm);
    ASSERT_TRUE(SUT.clear_error());
    ASSERT_TRUE(SUT.update(1.0));
    ASSERT_TRUE(SUT.get_ready_to_arm().ready_to_arm);
    fast::rf::messages::SensorMsgs::ImuMsg imu_data;
    ASSERT_TRUE(SUT.get_imu_data(imu_data));
    fast::rf::messages::SensorMsgs::MagneticFieldMsg magnetic_data;
    ASSERT_TRUE(SUT.get_magnetic_data(magnetic_data));
}

TEST(IMUProcess, BasicTests) {
    IMUProcess SUT;
    IIMUProcess::IMUConfig imu_config;
    imu_config.imu_type = IIMUDriver::convert_name("MOCK");
    imu_config.imu_device_name = "";
    ASSERT_TRUE(SUT.init(imu_config));
    ASSERT_TRUE(SUT.update(0.1));
    auto diagnostics = SUT.get_diagnostics();
    ASSERT_GT(diagnostics.size(), 0);
    fast::rf::Logger::log_notice(SUT.pretty());
    for (auto diagnostic : diagnostics) {
        ASSERT_NE(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
        ASSERT_LT(diagnostic.level, fast::rf::Level::WARN);
    }
    ASSERT_TRUE(SUT.get_ready_to_arm().ready_to_arm);
    fast::rf::messages::SensorMsgs::ImuMsg imu_data;
    ASSERT_TRUE(SUT.get_imu_data(imu_data));
    fast::rf::messages::SensorMsgs::MagneticFieldMsg magnetic_data;
    ASSERT_TRUE(SUT.get_magnetic_data(magnetic_data));
}
TEST(IMUProcess, BadDriverConfiguration) {
    IMUProcess SUT;
    IIMUProcess::IMUConfig imu_config;
    imu_config.imu_type = IIMUDriver::convert_name("UNKNOWN");
    imu_config.imu_device_name = "";
    ASSERT_FALSE(SUT.init(imu_config));
    ASSERT_FALSE(SUT.update(0.1));
    auto diagnostics = SUT.get_diagnostics();
    ASSERT_GT(diagnostics.size(), 0);
    fast::rf::Logger::log_notice(SUT.pretty());

    ASSERT_FALSE(SUT.get_ready_to_arm().ready_to_arm);
}