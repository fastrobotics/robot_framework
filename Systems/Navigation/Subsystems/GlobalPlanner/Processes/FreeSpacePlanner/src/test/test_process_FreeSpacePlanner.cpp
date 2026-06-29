

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseFreeSpacePlannerProcess.hpp>
#include <IFreeSpacePlannerProcess.hpp>

using namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem;
class TestFreeSpacePlannerProcessInterface : public IFreeSpacePlannerProcess {
   public:
    bool update(double current_time_sec, double delta_time_sec) override { return false; }
};
TEST(TestFreeSpacePlannerProcessInterface, InterfaceTests) {
    TestFreeSpacePlannerProcessInterface SUT;
    ASSERT_FALSE(SUT.update(0.0, 0.0));
}
class TestBaseFreeSpacePlannerProcess : public BaseFreeSpacePlannerProcess {
   public:
    TestBaseFreeSpacePlannerProcess() : BaseFreeSpacePlannerProcess() {}

    bool update(double current_time_sec, double delta_time_sec) override {
        return base_update(current_time_sec, delta_time_sec);
    }
};
TEST(BaseFreeSpacePlannerProcess, BasicAssertions) {
    TestBaseFreeSpacePlannerProcess SUT;
    ASSERT_TRUE(SUT.update(0.0, 0.0));
}