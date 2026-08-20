

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseInertialSensorFuserProcess.hpp>
#include <IInertialSensorFuserProcess.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::PoseSystem::LocalPoseSubsystem::InertialSensorFuser;
class TestInertialSensorFuserProcessInterface : public IInertialSensorFuserProcess {
   public:
    bool init([[maybe_unused]] uint8_t imu_count) { return true; }
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
    bool new_imu_data([[maybe_unused]] uint8_t imu_index,
                      [[maybe_unused]] fast::rf::messages::SensorMsgs::ImuMsg imu_data) {
        return false;
    }
    bool get_machine_inertial_data(fast::rf::messages::SensorMsgs::ImuMsg& imu_msg) {
        fast::rf::messages::SensorMsgs::ImuMsg data;
        imu_msg = data;
        return false;
    }
};
TEST(TestInertialSensorFuserProcessInterface, InterfaceTests) {
    TestInertialSensorFuserProcessInterface SUT;
    ASSERT_TRUE(SUT.init(0));

    ASSERT_EQ(SUT.get_diagnostics().size(), 0);
    ASSERT_FALSE(SUT.update(0.0));
}
class TestBaseInertialSensorFuserProcess : public BaseInertialSensorFuserProcess {
   public:
    TestBaseInertialSensorFuserProcess() : BaseInertialSensorFuserProcess() {}
    bool init(uint8_t imu_count) override {
        bool status = BaseInertialSensorFuserProcess::init(imu_count);
        if (status == false) {
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
    bool update(double current_time_sec) override { return BaseInertialSensorFuserProcess::update(current_time_sec); }
    std::string pretty() {
        std::string str = "---Test-Base---\n";
        str += BaseInertialSensorFuserProcess::pretty();
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
    bool new_imu_data([[maybe_unused]] uint8_t imu_index, fast::rf::messages::SensorMsgs::ImuMsg imu_data) {
        new_machine_inertial_data(imu_data);
        return true;
    }
};
TEST(BaseInertialSensorFuserProcess, FailureTests) {
    TestBaseInertialSensorFuserProcess SUT;
    ASSERT_FALSE(SUT.init(0));
    ASSERT_TRUE(SUT.init(1));
}
TEST(BaseInertialSensorFuserProcess, BasicAssertions) {
    TestBaseInertialSensorFuserProcess SUT;
    ASSERT_TRUE(SUT.init(1));
    ASSERT_GT(SUT.get_diagnostics().size(), 0);
    ASSERT_TRUE(SUT.update(0.0));
    ASSERT_TRUE(SUT.inject_error());
    ASSERT_TRUE(SUT.update(1.0));
    ASSERT_FALSE(SUT.get_ready_to_arm().ready_to_arm);
    ASSERT_TRUE(SUT.clear_error());
    ASSERT_TRUE(SUT.update(1.0));
    ASSERT_TRUE(SUT.get_ready_to_arm().ready_to_arm);
    fast::rf::Logger::log_debug(SUT.pretty());
    fast::rf::messages::SensorMsgs::ImuMsg sensor_imu_data;
    ASSERT_TRUE(SUT.new_imu_data(0, sensor_imu_data));
    fast::rf::Logger::log_debug(SUT.pretty());
    fast::rf::messages::SensorMsgs::ImuMsg machine_inertial_data;
    ASSERT_TRUE(SUT.get_machine_inertial_data(machine_inertial_data));
    fast::rf::Logger::log_debug(SUT.pretty());
    ASSERT_FALSE(SUT.get_machine_inertial_data(machine_inertial_data));
    fast::rf::Logger::log_debug(SUT.pretty());
}