/**
 * @compare_tag Process-BasicSourceTest v0.1
 *
 */

#include <gtest/gtest.h>
#include <stdio.h>

#include <BasicTrajectorySelectorProcess/BasicTrajectorySelectorProcess.hpp>

using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectorySelector;

TEST(BasicTrajectorySelectorProcess, BasicTests) {
    BasicTrajectorySelectorProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0));
}
TEST(BasicTrajectorySelectorProcess, BasicConversionTests) {
    BasicTrajectorySelectorProcess SUT;
    ASSERT_TRUE(SUT.init());
}
