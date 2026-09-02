

#include <gtest/gtest.h>
#include <stdio.h>

#include <Infrastructure/Logger.hpp>
#include <ServoHatDriverProcess/MockServoHatDriver.hpp>
using namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver;

TEST(MockServoHatDriver, BasicTests) {
    MockServoHatDriver SUT;
    ASSERT_TRUE(SUT.init());
    fast::rf::Logger::logInfo(SUT.pretty());

    ASSERT_TRUE(SUT.setServoValue(0, 0));
}