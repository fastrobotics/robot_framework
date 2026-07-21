

#include <gtest/gtest.h>
#include <stdio.h>

#include <ArmCommandMsg.hpp>
#include <Infrastructure/Logger.hpp>
#include <ServoHatDriverProcess/ServoHatDriverProcess.hpp>

using namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem;

TEST(ServoHatDriverProcess, BasicTests) {
    ServoHatDriverProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0));
    fast::rf::messages::InfrastructureMsgs::ArmCommandMsg robot_arm_command;
    robot_arm_command.armed_state = fast::rf::ArmedState::DISARMED;
    SUT.update_RobotArmCommand(robot_arm_command);
    ASSERT_TRUE(SUT.setServoValue(0, 0));
    robot_arm_command.armed_state = fast::rf::ArmedState::ARMED;
    SUT.update_RobotArmCommand(robot_arm_command);
    ASSERT_TRUE(SUT.setServoValue(0, 0));
    auto diagnostics = SUT.get_diagnostics();
    ASSERT_GT(diagnostics.size(), 0);
    for (auto diagnostic : diagnostics) {
        ASSERT_NE(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
        ASSERT_LT(diagnostic.level, fast::rf::Level::WARN);
    }
    ASSERT_TRUE(SUT.update(0.0));
    fast::rf::Logger::log_debug(SUT.pretty());
    ASSERT_TRUE(SUT.get_ready_to_arm().ready_to_arm);
}
TEST(ServoHatDriverProcess, BasicConversionTests) {
    ServoHatDriverProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(true);
}