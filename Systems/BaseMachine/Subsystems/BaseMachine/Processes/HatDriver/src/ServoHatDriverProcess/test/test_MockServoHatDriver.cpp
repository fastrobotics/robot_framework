

#include <gtest/gtest.h>
#include <stdio.h>

#include <Infrastructure/Logger.hpp>
#include <ServoHatDriverProcess/MockServoHatDriver.hpp>

using namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem;

TEST(MockServoHatDriver, BasicTests) {
    fast::rf::Logger::init(fast::rf::Level::DEBUG, "ServoHatDriver");
    MockServoHatDriver SUT;
    ASSERT_TRUE(SUT.init());
    fast::rf::Logger::log_info(SUT.pretty());
    ASSERT_TRUE(SUT.setServoValue(0, 0));
}