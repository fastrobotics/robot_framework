

#include <GeometryMsgs.hpp>
#include <TankDriveExecutorProcess/TankDriveExecutorProcess.hpp>

#include <TankDriveExecutorProcess/TankDriveExecutorOutput.hpp>

#include <IDriveExecutorOutput.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::rf::messages;
using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem;

TEST(TankDriveExecutorProcess, AssertionTests) {
  TankDriveExecutorProcess SUT;
  ASSERT_TRUE(SUT.update(0.0, 0.0));
}
TEST(TankDriveExecutorProcess, UserInterfaceTests) {
  TankDriveExecutorProcess SUT;
  TankDriveChannelConfig left_channel_config(1000.0, 1500.0, 2000.0);
  TankDriveChannelConfig right_channel_config(1000.0, 1500.0, 2000.0);
  SUT.set_config(left_channel_config, right_channel_config);
  GeometryMsgs::TwistMsg cmd;
  IDriveExecutorOutput *general_output = SUT.new_cmd(cmd);
  ASSERT_NE(general_output, nullptr);
  {

    TankDriveExecutorOutput *output =
        dynamic_cast<TankDriveExecutorOutput *>(general_output);
    ASSERT_NE(output, nullptr);
    ASSERT_EQ(output->left_drive, 1500.0);
    ASSERT_EQ(output->right_drive, 1500.0);
  }
}