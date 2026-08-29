
#include <gtest/gtest.h>
#include <stdio.h>

#include <ArmCommandMsg.hpp>
#include <ArmStateChangeSrv.hpp>
#include <ArmStateCommander.hpp>
#include <Infrastructure/Logger.hpp>
using namespace fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager;
TEST(ArmStateCommander, InterfaceTests) {
    ArmStateCommander SUT;
    ASSERT_TRUE(SUT.init());
    auto str = SUT.pretty();
    ASSERT_GT(str.size(), 0);
    fast::rf::Logger::logDebug(SUT.pretty());
    ASSERT_TRUE(SUT.update(0.0));
    ASSERT_TRUE(SUT.update_ready_to_arm(false));

    fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvRequest request;
    request.requested_armed_state = fast::rf::ArmedState::ARMED;
    auto response = SUT.request_armstate_change(request);
    ASSERT_FALSE(response.request_approved);

    ASSERT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::DISARMED_CANNOTARM);
}

TEST(ArmStateCommander, HappyFlowDisarmArm) {
    double current_time = 0.0;
    ArmStateCommander SUT;
    ASSERT_TRUE(SUT.init());
    auto str = SUT.pretty();
    ASSERT_GT(str.size(), 0);
    ASSERT_TRUE(SUT.update(0.0));
    ASSERT_TRUE(SUT.update_ready_to_arm(true));
    ASSERT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::DISARMED);

    fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvRequest request;
    request.requested_armed_state = fast::rf::ArmedState::ARMED;
    auto response = SUT.request_armstate_change(request);
    ASSERT_TRUE(response.request_approved);
    ASSERT_EQ(response.current_armed_state, fast::rf::ArmedState::ARMING);
    ASSERT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::ARMING);
    current_time += 0.1;
    ASSERT_TRUE(SUT.update(current_time));

    ASSERT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::ARMING);

    current_time += ArmStateCommander::ARMING_HOLD_TIME;
    ASSERT_TRUE(SUT.update(current_time));
    fast::rf::Logger::logInfo(SUT.pretty());
    ASSERT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::ARMED);

    current_time += 0.1;
    ASSERT_TRUE(SUT.update(current_time));
    ASSERT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::ARMED);

    request.requested_armed_state = fast::rf::ArmedState::DISARMED;
    response = SUT.request_armstate_change(request);
    ASSERT_TRUE(response.request_approved);
    ASSERT_EQ(response.current_armed_state, fast::rf::ArmedState::DISARMED);
    ASSERT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::DISARMED);
    fast::rf::Logger::logInfo(SUT.pretty());

    ASSERT_TRUE(SUT.update_ready_to_arm(false));
    ASSERT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::DISARMED_CANNOTARM);

    request.requested_armed_state = fast::rf::ArmedState::DISARMED;
    response = SUT.request_armstate_change(request);
    ASSERT_FALSE(response.request_approved);
    ASSERT_EQ(response.current_armed_state, fast::rf::ArmedState::DISARMED_CANNOTARM);
    ASSERT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::DISARMED_CANNOTARM);

    request.requested_armed_state = fast::rf::ArmedState::UNKNOWN;
    response = SUT.request_armstate_change(request);
    ASSERT_FALSE(response.request_approved);
    ASSERT_EQ(response.current_armed_state, fast::rf::ArmedState::DISARMED_CANNOTARM);
    ASSERT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::DISARMED_CANNOTARM);
    fast::rf::Logger::logInfo(SUT.pretty());

    ASSERT_TRUE(SUT.update_ready_to_arm(true));
    ASSERT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::DISARMED);

    ASSERT_TRUE(SUT.update_ready_to_arm(true));
    ASSERT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::DISARMED);

    request.requested_armed_state = fast::rf::ArmedState::ARMED;
    response = SUT.request_armstate_change(request);
    ASSERT_TRUE(response.request_approved);
    ASSERT_EQ(response.current_armed_state, fast::rf::ArmedState::ARMING);
    ASSERT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::ARMING);
    fast::rf::Logger::logInfo(SUT.pretty());
    current_time += 0.1;

    request.requested_armed_state = fast::rf::ArmedState::DISARMED;
    response = SUT.request_armstate_change(request);
    ASSERT_TRUE(response.request_approved);
    ASSERT_EQ(response.current_armed_state, fast::rf::ArmedState::DISARMED);
    ASSERT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::DISARMED);
    fast::rf::Logger::logInfo(SUT.pretty());
}