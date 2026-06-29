

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseTrajectorySelectorProcess.hpp>
#include <ITrajectorySelectorProcess.hpp>

using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem;
class TestTrajectorySelectorProcessInterface : public ITrajectorySelectorProcess {
   public:
    bool update(double current_time_sec, double delta_time_sec) override { return false; }
};
TEST(TestTrajectorySelectorProcessInterface, InterfaceTests) {
    TestTrajectorySelectorProcessInterface SUT;
    ASSERT_FALSE(SUT.update(0.0, 0.0));
}
class TestBaseTrajectorySelectorProcess : public BaseTrajectorySelectorProcess {
   public:
    TestBaseTrajectorySelectorProcess() : BaseTrajectorySelectorProcess() {}

    bool update(double current_time_sec, double delta_time_sec) override {
        return base_update(current_time_sec, delta_time_sec);
    }
};
TEST(BaseTrajectorySelectorProcess, BasicAssertions) {
    TestBaseTrajectorySelectorProcess SUT;
    ASSERT_TRUE(SUT.update(0.0, 0.0));
}