/**
 * @compare_tag Process-BasicSourceTest v0.1
 *
 */
#include <gtest/gtest.h>
#include <stdio.h>

#include <BasicDriveExecutorProcess/BasicDriveExecutorProcess.hpp>

using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::DriveExecutor;

TEST(BasicDriveExecutorProcess, BasicTests) {
    BasicDriveExecutorProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0));
}
TEST(BasicDriveExecutorProcess, BasicConversionTests) {
    BasicDriveExecutorProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.pretty().size(), 0);
}
