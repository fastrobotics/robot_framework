
#include <gtest/gtest.h>
#include <stdio.h>

#include <ArmStateChangeSrv.hpp>
using namespace fast::rf::messages::InfrastructureMsgs;
TEST(ArmStateChangeSrv, DefaultZeroConstructorRequest) {
    ArmStateChangeSrv::ArmStateChangeSrvRequest SUT;
    ASSERT_EQ(SUT.requested_armed_state, fast::rf::ArmedState::UNKNOWN);
}
TEST(ArmStateChangeSrv, DefaultZeroConstructorResponse) {
    ArmStateChangeSrv::ArmStateChangeSrvResponse SUT;
    ASSERT_EQ(SUT.current_armed_state, fast::rf::ArmedState::UNKNOWN);
    ASSERT_EQ(SUT.request_approved, false);
}
TEST(ArmStateChangeSrv, DefaultZeroConstructorService) {
    [[maybe_unused]] ArmStateChangeSrv SUT;
    ASSERT_TRUE(true);
}