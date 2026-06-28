

#include <BasicGlobalPathRoutePlannerProcess/BasicGlobalPathRoutePlannerProcess.hpp>

#include <gtest/gtest.h>
#include <stdio.h>

using namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem;

TEST(BasicGlobalPathRoutePlannerProcess, BasicTests) {
  BasicGlobalPathRoutePlannerProcess SUT;
  ASSERT_TRUE(SUT.update(0.0, 0.0));
}
TEST(BasicGlobalPathRoutePlannerProcess, BasicConversionTests) {
  BasicGlobalPathRoutePlannerProcess SUT;
  ASSERT_TRUE(true);
}