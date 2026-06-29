

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseGlobalPlannerManagerProcess.hpp>
#include <IGlobalPlannerManagerProcess.hpp>

using namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem;
class TestGlobalPlannerManagerProcessInterface : public IGlobalPlannerManagerProcess {
   public:
    bool update(double current_time_sec, double delta_time_sec) override { return false; }
};
TEST(TestGlobalPlannerManagerProcessInterface, InterfaceTests) {
    TestGlobalPlannerManagerProcessInterface SUT;
    ASSERT_FALSE(SUT.update(0.0, 0.0));
}
class TestBaseGlobalPlannerManagerProcess : public BaseGlobalPlannerManagerProcess {
   public:
    TestBaseGlobalPlannerManagerProcess() : BaseGlobalPlannerManagerProcess() {}

    bool update(double current_time_sec, double delta_time_sec) override {
        return base_update(current_time_sec, delta_time_sec);
    }
};
TEST(BaseGlobalPlannerManagerProcess, BasicAssertions) {
    TestBaseGlobalPlannerManagerProcess SUT;
    ASSERT_TRUE(SUT.update(0.0, 0.0));
}