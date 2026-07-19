

#include <gtest/gtest.h>
#include <stdio.h>

#include <IDriveExecutorOutput.hpp>
#include <Infrastructure/Logger.hpp>
#include <TankDriveExecutorProcess/TankDriveExecutorOutput.hpp>
#include <TankDriveExecutorProcess/TankDriveExecutorProcess.hpp>
#include <TwistMsg.hpp>
using namespace fast::rf::messages;
using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem;

TEST(TankDriveExecutorProcess, AssertionTests) {
    TankDriveExecutorProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0));
}
TEST(TankDriveExecutorProcess, NegativeAssertionTests) {
    TankDriveExecutorProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0));
    TankDriveChannelConfig left_config(2000.0, 1500.0, 1000.0);
    ASSERT_FALSE(left_config.is_ok());
    TankDriveChannelConfig right_config(1000.0, 1500.0, 1000.0);
    ASSERT_FALSE(right_config.is_ok());
    ASSERT_FALSE(SUT.set_config(left_config, right_config));
}
TEST(TankDriveExecutorProcess, UserInterfaceTests) {
    TankDriveExecutorProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.get_diagnostics().size(), 0);

    TankDriveChannelConfig left_channel_config(1000.0, 1500.0, 2000.0);
    TankDriveChannelConfig right_channel_config(1000.0, 1500.0, 2000.0);
    SUT.set_config(left_channel_config, right_channel_config);
    GeometryMsgs::TwistMsg cmd;
    IDriveExecutorOutput* general_output = SUT.new_cmd(cmd);
    for (const auto& diagnostic : SUT.get_diagnostics()) {
        ASSERT_EQ(diagnostic.level, fast::rf::Level::NOERROR);
        ASSERT_EQ(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR);
    }
    ASSERT_TRUE(SUT.update(0.0));
    fast::rf::Logger::log_debug(SUT.pretty());

    ASSERT_TRUE(SUT.get_ready_to_arm().ready_to_arm);
    ASSERT_NE(general_output, nullptr);
    {
        auto output = dynamic_cast<TankDriveExecutorOutput*>(general_output);
        ASSERT_NE(output, nullptr);
        ASSERT_EQ(output->left_drive, 1500.0);
        ASSERT_EQ(output->right_drive, 1500.0);
    }
    general_output = SUT.get_output();
    {
        auto output = dynamic_cast<TankDriveExecutorOutput*>(general_output);
        ASSERT_NE(output, nullptr);
        ASSERT_EQ(output->left_drive, 1500.0);
        ASSERT_EQ(output->right_drive, 1500.0);
    }
    printf("%s", SUT.pretty().c_str());
}