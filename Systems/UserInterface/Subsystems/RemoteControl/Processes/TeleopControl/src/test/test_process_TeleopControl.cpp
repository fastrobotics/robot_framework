

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseTeleopControlProcess.hpp>
#include <ITeleopControlProcess.hpp>

using namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem;
class TestTeleopControlProcessInterface : public ITeleopControlProcess {
   public:
    bool init([[maybe_unused]] ControlDevice device) { return true; }
    bool update([[maybe_unused]] double current_time_sec) override { return false; }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> empty;

        return empty;
    }
    bool new_joy([[maybe_unused]] fast::rf::messages::SensorMsgs::JoyMsg joy) { return false; }
    bool set_operation_mode([[maybe_unused]] OperationMode mode) { return false; }
    fast::rf::messages::GeometryMsgs::TwistMsg get_twist_output() {
        fast::rf::messages::GeometryMsgs::TwistMsg twist;
        return twist;
    }
    std::string pretty() { return "Test"; }
};
TEST(TestTeleopControlProcessInterface, InterfaceTests) {
    TestTeleopControlProcessInterface SUT;
    ASSERT_TRUE(SUT.init(ControlDevice::THRUSTMASTER_JOYSTICK));
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
    bool init([[maybe_unused]] ControlDevice device) override {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
    bool update([[maybe_unused]] double current_time_sec) override { return base_update(current_time_sec); }
    bool new_joy([[maybe_unused]] fast::rf::messages::SensorMsgs::JoyMsg joy) { return false; }
};
TEST(BaseTeleopControlProcess, BasicAssertions) {
    TestBaseTeleopControlProcess SUT;
    ASSERT_TRUE(SUT.init(ControlDevice::THRUSTMASTER_JOYSTICK));
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
}