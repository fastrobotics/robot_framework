

#include <gtest/gtest.h>
#include <stdio.h>

#include <ServoHatDriverProcess/ServoHatDriverProcess.hpp>

using namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem;

TEST(ServoHatDriverProcess, BasicTests) {
    ServoHatDriverProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0, 0.0));
}
TEST(ServoHatDriverProcess, BasicConversionTests) {
    ServoHatDriverProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(true);
}