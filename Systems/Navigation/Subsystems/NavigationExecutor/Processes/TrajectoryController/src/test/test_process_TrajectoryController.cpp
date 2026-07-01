

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseTrajectoryControllerProcess.hpp>
#include <ITrajectoryControllerProcess.hpp>

using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem;
class TestTrajectoryControllerProcessInterface : public ITrajectoryControllerProcess {
   public:
    bool update(double current_time_sec, [[maybe_unused]] double delta_time_sec) override { return false; }
};
TEST(TestTrajectoryControllerProcessInterface, InterfaceTests) {
    TestTrajectoryControllerProcessInterface SUT;
    ASSERT_FALSE(SUT.update(0.0, 0.0));
}
class TestBaseTrajectoryControllerProcess : public BaseTrajectoryControllerProcess {
   public:
    TestBaseTrajectoryControllerProcess() : BaseTrajectoryControllerProcess() {}

    bool update(double current_time_sec, [[maybe_unused]] double delta_time_sec) override {
        return base_update(current_time_sec, delta_time_sec);
    }
};
TEST(BaseTrajectoryControllerProcess, BasicAssertions) {
    TestBaseTrajectoryControllerProcess SUT;
    ASSERT_TRUE(SUT.update(0.0, 0.0));
}