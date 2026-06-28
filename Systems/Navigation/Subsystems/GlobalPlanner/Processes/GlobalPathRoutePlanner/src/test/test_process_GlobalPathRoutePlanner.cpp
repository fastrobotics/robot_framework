

#include <IGlobalPathRoutePlannerProcess.hpp>

#include <BaseGlobalPathRoutePlannerProcess.hpp>

#include <gtest/gtest.h>
#include <stdio.h>

using namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem;
class TestGlobalPathRoutePlannerProcessInterface : public IGlobalPathRoutePlannerProcess {
public:
  bool update(double current_time_sec, double delta_time_sec) override {
    return false;
  }
};
TEST(TestGlobalPathRoutePlannerProcessInterface, InterfaceTests) {
  TestGlobalPathRoutePlannerProcessInterface SUT;
  ASSERT_FALSE(SUT.update(0.0, 0.0));
}
class TestBaseGlobalPathRoutePlannerProcess : public BaseGlobalPathRoutePlannerProcess {
public:
  TestBaseGlobalPathRoutePlannerProcess() : BaseGlobalPathRoutePlannerProcess() {}

  bool update(double current_time_sec, double delta_time_sec) override {
    return base_update(current_time_sec, delta_time_sec);
  }
};
TEST(BaseGlobalPathRoutePlannerProcess, BasicAssertions) {
  TestBaseGlobalPathRoutePlannerProcess SUT;
  ASSERT_TRUE(SUT.update(0.0, 0.0));
}