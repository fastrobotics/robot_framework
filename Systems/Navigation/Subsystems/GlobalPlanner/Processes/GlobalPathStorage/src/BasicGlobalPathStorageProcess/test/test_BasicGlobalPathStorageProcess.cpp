

#include <gtest/gtest.h>
#include <stdio.h>

#include <BasicGlobalPathStorageProcess/BasicGlobalPathStorageProcess.hpp>

using namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem;

TEST(BasicGlobalPathStorageProcess, BasicTests) {
    BasicGlobalPathStorageProcess SUT;
    ASSERT_TRUE(SUT.update(0.0, 0.0));
}
TEST(BasicGlobalPathStorageProcess, BasicConversionTests) {
    BasicGlobalPathStorageProcess SUT;
    ASSERT_TRUE(true);
}