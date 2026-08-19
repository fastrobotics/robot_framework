

#include <gtest/gtest.h>
#include <stdio.h>

#include <BasicHatDriverProcess/BasicHatDriverProcess.hpp>

using namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver;

TEST(BasicHatDriverProcess, BasicTests) {
    BasicHatDriverProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0));
}
TEST(BasicHatDriverProcess, BasicConversionTests) {
    BasicHatDriverProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.pretty().size(), 0);
}