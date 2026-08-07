

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseTeleopControlProcess.hpp>
#include <ITeleopControlProcess.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem;
class TestTeleopControlProcessInterface : public ITeleopControlProcess {
   public:
    bool init([[maybe_unused]] ControlDevice device, [[maybe_unused]] JoystickCalibrationData joy_calibration_data) {
        return true;
    }
    bool update([[maybe_unused]] double current_time_sec) override { return false; }
    void update_RobotArmCommand([
        [maybe_unused]] fast::rf::messages::InfrastructureMsgs::ArmCommandMsg robot_arm_command) {}
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> empty;

        return empty;
    }
    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() {
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;
        return ready_to_arm;
    }
    bool new_joy([[maybe_unused]] fast::rf::messages::SensorMsgs::JoyMsg joy) { return false; }
    bool set_operation_mode([[maybe_unused]] OperationMode mode) { return false; }
    fast::rf::messages::GeometryMsgs::TwistMsg get_twist_output() {
        fast::rf::messages::GeometryMsgs::TwistMsg twist;
        return twist;
    }
    fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvRequest get_armstate_change_request() {
        fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvRequest request;
        return request;
    }
    std::string pretty() { return "Test"; }
};
TEST(TestTeleopControlProcessInterface, InterfaceTests) {
    TestTeleopControlProcessInterface SUT;
    JoystickCalibrationData joy_calibration;
    joy_calibration.optional_init();
    ASSERT_TRUE(SUT.init(ControlDevice::THRUSTMASTER_JOYSTICK, joy_calibration));
    ASSERT_EQ(SUT.get_diagnostics().size(), 0);
    ASSERT_FALSE(SUT.update(0.0));
    ASSERT_FALSE(SUT.new_joy(fast::rf::messages::SensorMsgs::JoyMsg{}));
    auto twist = SUT.get_twist_output();
    ASSERT_FLOAT_EQ(twist.linear.x, 0.0);
    ASSERT_FLOAT_EQ(twist.linear.y, 0.0);
    ASSERT_FLOAT_EQ(twist.linear.z, 0.0);
    ASSERT_FLOAT_EQ(twist.angular.x, 0.0);
    ASSERT_FLOAT_EQ(twist.angular.y, 0.0);
    ASSERT_FLOAT_EQ(twist.angular.z, 0.0);
}
class TestBaseTeleopControlProcess : public BaseTeleopControlProcess {
   public:
    TestBaseTeleopControlProcess() : BaseTeleopControlProcess() {}
    bool init([[maybe_unused]] ControlDevice device,
              [[maybe_unused]] JoystickCalibrationData joy_calibration_data) override {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
    bool update([[maybe_unused]] double current_time_sec) override {
        return BaseTeleopControlProcess::update(current_time_sec);
    }
    std::string pretty() {
        std::string str = "---Test-Base---\n";
        str += BaseTeleopControlProcess::pretty();
        return str;
    }
    bool new_joy([[maybe_unused]] fast::rf::messages::SensorMsgs::JoyMsg joy) { return false; }
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
};
TEST(BaseTeleopControlProcess, BasicAssertions) {
    TestBaseTeleopControlProcess SUT;
    JoystickCalibrationData joy_calibration;
    joy_calibration.optional_init();
    ASSERT_TRUE(SUT.init(ControlDevice::THRUSTMASTER_JOYSTICK, joy_calibration));
    for (uint8_t mode = 0;
         mode <= (uint8_t)fast::rf::UserInterfaceSystem::RemoteControlSubsystem::OperationMode::END_OF_LIST; ++mode) {
        if ((mode == 0) ||
            (mode == (uint8_t)fast::rf::UserInterfaceSystem::RemoteControlSubsystem::OperationMode::END_OF_LIST)) {
            ASSERT_FALSE(
                SUT.set_operation_mode((fast::rf::UserInterfaceSystem::RemoteControlSubsystem::OperationMode)mode));
        } else {
            ASSERT_TRUE(
                SUT.set_operation_mode((fast::rf::UserInterfaceSystem::RemoteControlSubsystem::OperationMode)mode));
            printf("%s\n", SUT.pretty().c_str());
        }
    }
    ASSERT_TRUE(SUT.set_operation_mode(fast::rf::UserInterfaceSystem::RemoteControlSubsystem::OperationMode::RUN));
    ASSERT_GT(SUT.get_diagnostics().size(), 0);
    ASSERT_TRUE(SUT.update(0.0));
    printf("%s\n", SUT.pretty().c_str());
    ASSERT_FALSE(SUT.new_joy(fast::rf::messages::SensorMsgs::JoyMsg{}));
    ASSERT_TRUE(SUT.inject_error());
    ASSERT_TRUE(SUT.update(1.0));
    ASSERT_FALSE(SUT.get_ready_to_arm().ready_to_arm);
    ASSERT_TRUE(SUT.clear_error());
    ASSERT_TRUE(SUT.update(1.0));
    ASSERT_TRUE(SUT.get_ready_to_arm().ready_to_arm);
    ASSERT_EQ(SUT.get_armstate_change_request().requested_armed_state, fast::rf::ArmedState::UNKNOWN);
}