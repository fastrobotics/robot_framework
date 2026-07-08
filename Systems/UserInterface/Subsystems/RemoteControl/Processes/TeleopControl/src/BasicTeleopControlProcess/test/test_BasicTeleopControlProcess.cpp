

#include <gtest/gtest.h>
#include <stdio.h>

#include <BasicTeleopControlProcess/BasicTeleopControlProcess.hpp>

using namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem;

TEST(BasicTeleopControlProcess, BasicTests) {
    BasicTeleopControlProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0, 0.0));
    printf("%s\n", SUT.pretty().c_str());
}
TEST(BasicTeleopControlProcess, BasicConversionTests) {
    BasicTeleopControlProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(true);
}