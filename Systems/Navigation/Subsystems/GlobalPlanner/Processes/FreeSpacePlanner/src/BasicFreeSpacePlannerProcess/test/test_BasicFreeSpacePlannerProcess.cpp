

#include <gtest/gtest.h>
#include <stdio.h>

#include <BasicFreeSpacePlannerProcess/BasicFreeSpacePlannerProcess.hpp>

using namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem;

TEST(BasicFreeSpacePlannerProcess, BasicTests) {
    BasicFreeSpacePlannerProcess SUT;
    ASSERT_TRUE(SUT.update(0.0, 0.0));
}
TEST(BasicFreeSpacePlannerProcess, BasicConversionTests) {
    BasicFreeSpacePlannerProcess SUT;
    ASSERT_TRUE(true);
}