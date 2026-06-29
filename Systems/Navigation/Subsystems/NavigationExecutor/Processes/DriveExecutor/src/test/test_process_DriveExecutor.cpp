

#include <IDriveExecutorProcess.hpp>

#include <BaseDriveExecutorProcess.hpp>

#include <IDriveExecutorOutput.hpp>

#include <gtest/gtest.h>

#include <stdio.h>

using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem;
class TestDriveExecutorOutput : public IDriveExecutorOutput {
public:
  int a{1};
};
class TestDriveExecutorProcessInterface : public IDriveExecutorProcess {
public:
  IDriveExecutorOutput *new_cmd(GeometryMsgs::TwistMsg cmd) override {
    return output;
  }
  bool update(double current_time_sec, double delta_time_sec) override {
    return false;
  }

private:
  TestDriveExecutorOutput *output = new TestDriveExecutorOutput();
};
TEST(TestDriveExecutorProcessInterface, InterfaceTests) {
  TestDriveExecutorProcessInterface SUT;
  ASSERT_FALSE(SUT.update(0.0, 0.0));
  GeometryMsgs::TwistMsg cmd;
  auto general_output = SUT.new_cmd(cmd);
  ASSERT_NE(general_output, nullptr);

  TestDriveExecutorOutput *output =
      dynamic_cast<TestDriveExecutorOutput *>(general_output);
  ASSERT_NE(output, nullptr);
  ASSERT_EQ(output->a, 1);
}
class TestBaseDriveExecutorProcess : public BaseDriveExecutorProcess {
public:
  TestBaseDriveExecutorProcess() : BaseDriveExecutorProcess() {}
  IDriveExecutorOutput *new_cmd(GeometryMsgs::TwistMsg cmd) override {
    return nullptr;
  }
  bool update(double current_time_sec, double delta_time_sec) override {
    return base_update(current_time_sec, delta_time_sec);
  }
};
TEST(BaseDriveExecutorProcess, BasicAssertions) {
  TestBaseDriveExecutorProcess SUT;
  ASSERT_TRUE(SUT.update(0.0, 0.0));
}