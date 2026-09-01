
#include <gtest/gtest.h>
#include <stdio.h>

#include <IDriveExecutorProcess.hpp>
#include <ITrajectoryControllerProcess.hpp>
#include <ITrajectorySelectorProcess.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem;
class TestTrajectorySelector : public TrajectorySelector::ITrajectorySelectorProcess {
   public:
    bool init() override { return true; }
    uint8_t getSystemId() override { return 0; }
    uint8_t getSubSystemId() override { return 0; }
    uint8_t getProcessId() override { return 0; }
    bool updateDiagnostic([[maybe_unused]] fast::rf::DiagnosticDefinition::DiagnosticType type,
                          [[maybe_unused]] fast::rf::Level level,
                          [[maybe_unused]] fast::rf::DiagnosticDefinition::DiagnosticMessage message,
                          [[maybe_unused]] std::string description) override {
        return false;
    }
    bool update([[maybe_unused]] double current_time_sec) override { return true; }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> diagnostics;
        return diagnostics;
    }
    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() override {
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;
        return ready_to_arm;
    }
    std::string pretty() override { return ""; }
};

class TestTrajectoryController : public TrajectoryController::ITrajectoryControllerProcess {
   public:
    bool init() override { return true; }
    uint8_t getSystemId() override { return 0; }
    uint8_t getSubSystemId() override { return 0; }
    uint8_t getProcessId() override { return 0; }
    bool updateDiagnostic([[maybe_unused]] fast::rf::DiagnosticDefinition::DiagnosticType type,
                          [[maybe_unused]] fast::rf::Level level,
                          [[maybe_unused]] fast::rf::DiagnosticDefinition::DiagnosticMessage message,
                          [[maybe_unused]] std::string description) override {
        return false;
    }
    bool update([[maybe_unused]] double current_time_sec) override { return true; }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> diagnostics;
        return diagnostics;
    }
    std::string pretty() override { return ""; }
    bool new_pose([[maybe_unused]] fast::rf::messages::GeometryMsgs::OdomMsg pose) override { return true; }
    bool new_desired_command([[maybe_unused]] fast::rf::messages::GeometryMsgs::TwistMsg cmd) override { return true; }
    bool get_command(fast::rf::messages::GeometryMsgs::TwistMsg& cmd) override {
        fast::rf::messages::GeometryMsgs::TwistMsg command;
        cmd = command;
        return true;
    }
    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() override {
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;
        return ready_to_arm;
    }
};

class TestDriveExecutor : public DriveExecutor::IDriveExecutorProcess {
   public:
    bool init() override { return true; }
    uint8_t getSystemId() override { return 0; }
    uint8_t getSubSystemId() override { return 0; }
    uint8_t getProcessId() override { return 0; }
    bool updateDiagnostic([[maybe_unused]] fast::rf::DiagnosticDefinition::DiagnosticType type,
                          [[maybe_unused]] fast::rf::Level level,
                          [[maybe_unused]] fast::rf::DiagnosticDefinition::DiagnosticMessage message,
                          [[maybe_unused]] std::string description) override {
        return false;
    }
    bool update([[maybe_unused]] double current_time_sec) override { return true; }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> diagnostics;
        return diagnostics;
    }
    std::string pretty() override { return ""; }
    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() override {
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;
        return ready_to_arm;
    }
    DriveExecutor::IDriveExecutorOutput* new_cmd([[maybe_unused]] GeometryMsgs::TwistMsg cmd) override {
        DriveExecutor::IDriveExecutorOutput* output = nullptr;
        return output;
    }
    DriveExecutor::IDriveExecutorOutput* get_output() {
        DriveExecutor::IDriveExecutorOutput* output = nullptr;
        return output;
    }
};

TEST(NavigationExecutorSubsystem, InterfaceTests) {
    fast::rf::Logger::logNotice("Testing Navigation Executor Interfaces (Function Signatures).");
    TestTrajectorySelector selector;
    TestTrajectoryController controller;
    TestDriveExecutor executor;

    // Initialization

    ASSERT_TRUE(selector.init());
    ASSERT_TRUE(controller.init());
    ASSERT_TRUE(executor.init());

    ASSERT_TRUE(selector.update(0.0));
    ASSERT_TRUE(controller.update(0.0));
    ASSERT_TRUE(executor.update(0.0));

    // Start a Control Cycle
    // Selector is not currently implemented/involved.

    fast::rf::messages::GeometryMsgs::OdomMsg pose;
    ASSERT_TRUE(controller.new_pose(pose));

    fast::rf::messages::GeometryMsgs::TwistMsg set_point_trajectory;
    ASSERT_TRUE(controller.new_desired_command(set_point_trajectory));

    fast::rf::messages::GeometryMsgs::TwistMsg execute_trajectory;
    ASSERT_TRUE(controller.get_command(execute_trajectory));

    auto drive_command = executor.new_cmd(execute_trajectory);
    ASSERT_EQ(drive_command, nullptr);  // Empty Data as this is testing interfaces
}