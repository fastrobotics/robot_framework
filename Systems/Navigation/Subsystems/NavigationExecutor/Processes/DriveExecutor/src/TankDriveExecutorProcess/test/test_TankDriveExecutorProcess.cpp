

#include <gtest/gtest.h>
#include <stdio.h>

#include <IDriveExecutorOutput.hpp>
#include <TankDriveExecutorProcess/TankDriveExecutorOutput.hpp>
#include <TankDriveExecutorProcess/TankDriveExecutorProcess.hpp>
#include <TwistMsg.hpp>
using namespace fast::rf::messages;
using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem;

TEST(TankDriveExecutorProcess, AssertionTests) {
    TankDriveExecutorProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0, 0.0));
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

TEST(TankDriveExecutorProcess, InitializesExpectedDiagnostics) {
    TankDriveExecutorProcess SUT;
    ASSERT_TRUE(SUT.init());

    auto diagnostics = SUT.get_diagnostics();
    ASSERT_EQ(diagnostics.size(), 3);

    bool saw_software = false;
    bool saw_remote_control = false;
    bool saw_actuators = false;

    for (const auto& diagnostic : diagnostics) {
        if (diagnostic.diagnosticType == fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE) {
            saw_software = true;
            ASSERT_EQ(diagnostic.level, fast::rf::Level::NOERROR);
            ASSERT_EQ(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR);
            ASSERT_EQ(diagnostic.description, "SW Running.");
        } else if (diagnostic.diagnosticType == fast::rf::DiagnosticDefinition::DiagnosticType::REMOTE_CONTROL) {
            saw_remote_control = true;
            ASSERT_EQ(diagnostic.level, fast::rf::Level::WARN);
            ASSERT_EQ(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::NODATA);
        } else if (diagnostic.diagnosticType == fast::rf::DiagnosticDefinition::DiagnosticType::ACTUATORS) {
            saw_actuators = true;
            ASSERT_EQ(diagnostic.level, fast::rf::Level::WARN);
            ASSERT_EQ(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::NODATA);
        }
    }

    ASSERT_TRUE(saw_software);
    ASSERT_TRUE(saw_remote_control);
    ASSERT_TRUE(saw_actuators);
}