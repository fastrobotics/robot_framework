

#include <gtest/gtest.h>
#include <stdio.h>

#include <BasicGlobalPathRoutePlannerProcess/BasicGlobalPathRoutePlannerProcess.hpp>

using namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem;

TEST(BasicGlobalPathRoutePlannerProcess, BasicTests) {
    BasicGlobalPathRoutePlannerProcess SUT;
    ASSERT_TRUE(SUT.update(0.0, 0.0));
}
TEST(BasicGlobalPathRoutePlannerProcess, BasicConversionTests) {
    BasicGlobalPathRoutePlannerProcess SUT;
    ASSERT_TRUE(true);
}