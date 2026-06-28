

#include <IDriveExecutorProcess.hpp>

#include <BaseDriveExecutorProcess.hpp>

#include <gtest/gtest.h>
#include <stdio.h>

using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem;
class TestDriveExecutorProcessInterface : public IDriveExecutorProcess {
public:
  bool update(double current_time_sec, double delta_time_sec) override {
    return false;
  }
};
TEST(TestDriveExecutorProcessInterface, InterfaceTests) {
  TestDriveExecutorProcessInterface SUT;
  ASSERT_FALSE(SUT.update(0.0, 0.0));
}
class TestBaseDriveExecutorProcess : public BaseDriveExecutorProcess {
public:
  TestBaseDriveExecutorProcess() : BaseDriveExecutorProcess() {}

  bool update(double current_time_sec, double delta_time_sec) override {
    return base_update(current_time_sec, delta_time_sec);
  }
};
TEST(BaseDriveExecutorProcess, BasicAssertions) {
  TestBaseDriveExecutorProcess SUT;
  ASSERT_TRUE(SUT.update(0.0, 0.0));
}