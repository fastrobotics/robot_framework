

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseGlobalPathStorageProcess.hpp>
#include <IGlobalPathStorageProcess.hpp>

using namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem;
class TestGlobalPathStorageProcessInterface : public IGlobalPathStorageProcess {
   public:
    bool update(double current_time_sec, double delta_time_sec) override { return false; }
};
TEST(TestGlobalPathStorageProcessInterface, InterfaceTests) {
    TestGlobalPathStorageProcessInterface SUT;
    ASSERT_FALSE(SUT.update(0.0, 0.0));
}
class TestBaseGlobalPathStorageProcess : public BaseGlobalPathStorageProcess {
   public:
    TestBaseGlobalPathStorageProcess() : BaseGlobalPathStorageProcess() {}

    bool update(double current_time_sec, double delta_time_sec) override {
        return base_update(current_time_sec, delta_time_sec);
    }
};
TEST(BaseGlobalPathStorageProcess, BasicAssertions) {
    TestBaseGlobalPathStorageProcess SUT;
    ASSERT_TRUE(SUT.update(0.0, 0.0));
}