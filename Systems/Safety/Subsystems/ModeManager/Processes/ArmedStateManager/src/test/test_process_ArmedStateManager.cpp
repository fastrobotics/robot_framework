

#include <gtest/gtest.h>
#include <stdio.h>

#include <ArmedStateManagerProcess.hpp>
#include <BaseArmedStateManagerProcess.hpp>
#include <IArmedStateManagerProcess.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager;
class TestArmedStateManagerProcessInterface : public IArmedStateManagerProcess {
   public:
    bool init() { return true; }
    bool update([[maybe_unused]] double current_time_sec) override { return false; }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> empty;

        return empty;
    }
    std::string pretty() override { return ""; }
    fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse request_armstate_change([
        [maybe_unused]] fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvRequest request)
        override {
        fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse response;
        response.request_approved = false;
        return response;
    }
    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() {
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;
        return ready_to_arm;
    }
    bool new_ReadyToArmStatus([
        [maybe_unused]] fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg msg) override {
        return false;
    }

    fast::rf::messages::InfrastructureMsgs::ArmCommandMsg get_ArmCommandMsg() {
        fast::rf::messages::InfrastructureMsgs::ArmCommandMsg arm_command;
        return arm_command;
    }
};
TEST(TestArmedStateManagerProcessInterface, InterfaceTests) {
    TestArmedStateManagerProcessInterface SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_EQ(SUT.get_diagnostics().size(), 0);
    ASSERT_FALSE(SUT.update(0.0));
    fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvRequest request;
    auto response = SUT.request_armstate_change(request);
    ASSERT_FALSE(response.request_approved);
    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm_msg;
    ASSERT_FALSE(SUT.new_ReadyToArmStatus(ready_to_arm_msg));
    ASSERT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::UNKNOWN);
}
class TestBaseArmedStateManagerProcess : public BaseArmedStateManagerProcess {
   public:
    TestBaseArmedStateManagerProcess() : BaseArmedStateManagerProcess() {}
    bool init() override {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
    bool update(double current_time_sec) override { return BaseArmedStateManagerProcess::update(current_time_sec); }
    fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse request_armstate_change([
        [maybe_unused]] fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvRequest request)
        override {
        fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse response;
        response.request_approved = false;
        return response;
    }

    bool new_ReadyToArmStatus([
        [maybe_unused]] fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg msg) override {
        return false;
    }
    fast::rf::messages::InfrastructureMsgs::ArmCommandMsg get_ArmCommandMsg() {
        fast::rf::messages::InfrastructureMsgs::ArmCommandMsg arm_command;
        return arm_command;
    }
};
TEST(BaseArmedStateManagerProcess, BasicAssertions) {
    TestBaseArmedStateManagerProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.get_diagnostics().size(), 0);
    ASSERT_TRUE(SUT.update(0.0));
    fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvRequest request;
    auto response = SUT.request_armstate_change(request);
    ASSERT_FALSE(response.request_approved);
    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm_msg;
    ASSERT_FALSE(SUT.new_ReadyToArmStatus(ready_to_arm_msg));
    ASSERT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::UNKNOWN);
}
TEST(ArmedStateManagerProcess, BasicTests) {
    ArmedStateManagerProcess SUT;
    double current_time = 0.0;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(current_time));
    auto diagnostics = SUT.get_diagnostics();
    ASSERT_GT(diagnostics.size(), 0);

    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg process1;
    process1.systemID = fast::rf::BaseMachineSystem::SYSTEM_ID;
    process1.subsystemID = fast::rf::BaseMachineSystem::BaseMachineSubsystem::SUBSYSTEM_ID;
    process1.processID = fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver::PROCESS_HATDRIVER_ID;
    process1.ready_to_arm = true;
    ASSERT_TRUE(SUT.new_ReadyToArmStatus(process1));

    fast::rf::Logger::log_info(SUT.pretty());
    diagnostics = SUT.get_diagnostics();
    ASSERT_GT(diagnostics.size(), 0);
    bool comms_diagnostic_check = false;
    for (auto diagnostic : diagnostics) {
        if (diagnostic.diagnosticType == fast::rf::DiagnosticDefinition::DiagnosticType::COMMUNICATIONS) {
            ASSERT_EQ(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::NODATA);
            comms_diagnostic_check = true;
        }
    }
    ASSERT_TRUE(comms_diagnostic_check);

    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg process2;
    process2.systemID = fast::rf::NavigationSystem::SYSTEM_ID;
    process2.subsystemID = fast::rf::NavigationSystem::NavigationExecutorSubsystem::SUBSYSTEM_ID;
    process2.processID =
        fast::rf::NavigationSystem::NavigationExecutorSubsystem::DriveExecutor::PROCESS_DRIVE_EXECUTOR_ID;
    process2.ready_to_arm = true;

    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg process3;
    process3.systemID = fast::rf::UserInterfaceSystem::SYSTEM_ID;
    process3.subsystemID = fast::rf::UserInterfaceSystem::RemoteControlSubsystem::SUBSYSTEM_ID;
    process3.processID = fast::rf::UserInterfaceSystem::RemoteControlSubsystem::TeleopControl::PROCESS_TELEOPCONTROL_ID;
    process3.ready_to_arm = true;

    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg process4;
    process4.systemID = fast::rf::NavigationSystem::SYSTEM_ID;
    process4.subsystemID = fast::rf::NavigationSystem::NavigationExecutorSubsystem::SUBSYSTEM_ID;
    process4.processID =
        fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectoryController::PROCESS_TRAJECTORY_CONTROLLER_ID;
    process4.ready_to_arm = true;

    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg process5;
    process5.systemID = fast::rf::PoseSystem::SYSTEM_ID;
    process5.subsystemID = fast::rf::PoseSystem::LocalPoseSubsystem::SUBSYSTEM_ID;
    process5.processID = fast::rf::PoseSystem::LocalPoseSubsystem::LocalPoseFuser::PROCESS_LOCALPOSEFUSER_ID;
    process5.ready_to_arm = true;

    ASSERT_TRUE(SUT.new_ReadyToArmStatus(process2));
    ASSERT_TRUE(SUT.new_ReadyToArmStatus(process3));
    ASSERT_TRUE(SUT.new_ReadyToArmStatus(process4));
    ASSERT_TRUE(SUT.new_ReadyToArmStatus(process5));
    current_time += 0.1;
    ASSERT_TRUE(SUT.update(current_time));

    current_time += 0.1 + ReadyToArmComputer::PROCESS_TIMEOUT_SEC;
    ASSERT_TRUE(SUT.update(current_time));

    fast::rf::Logger::log_info(SUT.pretty());
    diagnostics = SUT.get_diagnostics();
    ASSERT_GT(diagnostics.size(), 0);
    comms_diagnostic_check = false;
    for (auto diagnostic : diagnostics) {
        if (diagnostic.diagnosticType == fast::rf::DiagnosticDefinition::DiagnosticType::COMMUNICATIONS) {
            ASSERT_EQ(diagnostic.diagnosticMessage,
                      fast::rf::DiagnosticDefinition::DiagnosticMessage::DROPPING_PACKETS);
            comms_diagnostic_check = true;
        }
    }
    ASSERT_TRUE(comms_diagnostic_check);

    fast::rf::Logger::log_info(SUT.pretty());
    ASSERT_TRUE(SUT.new_ReadyToArmStatus(process1));
    ASSERT_TRUE(SUT.new_ReadyToArmStatus(process2));
    ASSERT_TRUE(SUT.new_ReadyToArmStatus(process3));
    ASSERT_TRUE(SUT.new_ReadyToArmStatus(process4));
    ASSERT_TRUE(SUT.new_ReadyToArmStatus(process5));
    current_time += 0.1;
    ASSERT_TRUE(SUT.update(current_time));
    ASSERT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::DISARMED);
    diagnostics = SUT.get_diagnostics();
    ASSERT_GT(diagnostics.size(), 0);
    for (auto diagnostic : diagnostics) {
        ASSERT_NE(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
        ASSERT_LT(diagnostic.level, fast::rf::Level::WARN);
    }
    fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvRequest request;
    request.requested_armed_state = fast::rf::ArmedState::ARMED;
    auto response = SUT.request_armstate_change(request);
    ASSERT_TRUE(response.request_approved);
    ASSERT_EQ(response.current_armed_state, fast::rf::ArmedState::ARMING);

    current_time += 0.1;
    ASSERT_TRUE(SUT.update(current_time));
    ASSERT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::ARMING);

    double elap_timer = 0.0;
    while (elap_timer <= (0.5 + ArmStateCommander::ARMING_HOLD_TIME)) {
        elap_timer += 0.1;
        current_time += 0.1;
        ASSERT_TRUE(SUT.new_ReadyToArmStatus(process1));
        ASSERT_TRUE(SUT.new_ReadyToArmStatus(process2));
        ASSERT_TRUE(SUT.new_ReadyToArmStatus(process3));
        ASSERT_TRUE(SUT.new_ReadyToArmStatus(process4));
        ASSERT_TRUE(SUT.new_ReadyToArmStatus(process5));
        ASSERT_TRUE(SUT.update(current_time));
    }

    fast::rf::Logger::log_info(SUT.pretty());

    ASSERT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::ARMED);
}
TEST(ArmedStateManagerProcess, FailureTestsUpdate) {
    ArmedStateManagerProcess SUT;
    // Test not calling Initialization

    ASSERT_FALSE(SUT.update(0.0));
}
TEST(ArmedStateManagerProcess, FailureTestsBadReadyToArm) {
    ArmedStateManagerProcess SUT;
    ASSERT_TRUE(SUT.init());

    ASSERT_TRUE(SUT.update(0.0));

    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg process1;
    process1.systemID = 0;
    process1.subsystemID = 0;
    process1.processID = 0;
    process1.ready_to_arm = true;
    ASSERT_FALSE(SUT.new_ReadyToArmStatus(process1));
}