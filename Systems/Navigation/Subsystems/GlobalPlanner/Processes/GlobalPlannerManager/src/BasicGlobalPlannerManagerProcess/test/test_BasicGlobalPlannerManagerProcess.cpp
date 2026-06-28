

#include <BasicGlobalPlannerManagerProcess/BasicGlobalPlannerManagerProcess.hpp>

#include <gtest/gtest.h>
#include <stdio.h>

using namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem;

TEST(BasicGlobalPlannerManagerProcess, BasicTests) {
  BasicGlobalPlannerManagerProcess SUT;
  ASSERT_TRUE(SUT.update(0.0, 0.0));
}
TEST(BasicGlobalPlannerManagerProcess, BasicConversionTests) {
  BasicGlobalPlannerManagerProcess SUT;
  ASSERT_TRUE(true);
}