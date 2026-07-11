

#include <gtest/gtest.h>
#include <stdio.h>

#include <ServoHatDriverProcess/MockServoHatDriver.hpp>

using namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem;

TEST(MockServoHatDriver, BasicTests) {
    MockServoHatDriver SUT;
    ASSERT_TRUE(SUT.init());
}