

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseTrajectoryControllerProcess.hpp>
#include <Controller/PIDController/PIDController.hpp>
#include <ITrajectoryControllerProcess.hpp>

using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectoryController;
class TestTrajectoryControllerProcessInterface : public ITrajectoryControllerProcess {
   public:
    bool init() override { return true; }
    bool update([[maybe_unused]] double current_time_sec) override { return false; }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> empty;

        return empty;
    }
    bool new_pose([[maybe_unused]] fast::rf::messages::GeometryMsgs::OdomMsg pose) { return false; }
    bool new_desired_command([[maybe_unused]] fast::rf::messages::GeometryMsgs::TwistMsg cmd) { return false; }
    bool get_command([[maybe_unused]] fast::rf::messages::GeometryMsgs::TwistMsg& cmd) { return false; }
    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() {
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;
        return ready_to_arm;
    }
    std::string pretty() { return ""; }
};
TEST(TestTrajectoryControllerProcessInterface, InterfaceTests) {
    TestTrajectoryControllerProcessInterface SUT;
    ASSERT_FALSE(SUT.update(0.0));
    ASSERT_EQ(SUT.pretty(), "");
}
class TestBaseTrajectoryControllerProcess : public BaseTrajectoryControllerProcess {
   public:
    TestBaseTrajectoryControllerProcess() : BaseTrajectoryControllerProcess() {}
    bool init() override {
        controller_ = new fast::rf::NavigationSystem::Controller::PIDController;
        bool status = BaseTrajectoryControllerProcess::init();
        if (status == false) {
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        status = diagnosticManager.initializeDiagnostics(diagnostic_types);
        return status;
    }
    bool update(double current_time_sec) override { return BaseTrajectoryControllerProcess::update(current_time_sec); }
    bool new_pose(fast::rf::messages::GeometryMsgs::OdomMsg pose) {
        return BaseTrajectoryControllerProcess::new_pose(pose);
    }
    bool new_desired_command(fast::rf::messages::GeometryMsgs::TwistMsg cmd) {
        set_command(cmd);
        return BaseTrajectoryControllerProcess::new_desired_command(cmd);
    }
    std::string pretty() { return BaseTrajectoryControllerProcess::pretty(); }
    bool inject_error() {
        return diagnosticManager.updateDiagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::ERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::DIAGNOSTIC_FAILED, "Testing Error Injection");
    }
    bool clear_error() {
        return diagnosticManager.updateDiagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::NOERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Clearing Error Injection");
    }
};
TEST(BaseTrajectoryControllerProcess, BasicAssertions) {
    TestBaseTrajectoryControllerProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.getDiagnostics().size(), 0);
    ASSERT_FALSE(SUT.get_ready_to_arm().ready_to_arm);
    fast::rf::Logger::logDebug(SUT.pretty());
    ASSERT_TRUE(SUT.update(0.0));
    ASSERT_TRUE(SUT.get_ready_to_arm().ready_to_arm);
    fast::rf::messages::GeometryMsgs::OdomMsg pose;
    ASSERT_TRUE(SUT.new_pose(pose));

    fast::rf::messages::GeometryMsgs::TwistMsg desired_command;
    desired_command.linear.x = 1.0;
    ASSERT_TRUE(SUT.new_desired_command(desired_command));
    fast::rf::messages::GeometryMsgs::TwistMsg command;
    ASSERT_TRUE(SUT.get_command(command));
    ASSERT_FLOAT_EQ(command.linear.x, 1.0);

    ASSERT_TRUE(SUT.inject_error());
    ASSERT_TRUE(SUT.update(1.0));
    ASSERT_FALSE(SUT.get_ready_to_arm().ready_to_arm);
    ASSERT_TRUE(SUT.clear_error());
    ASSERT_TRUE(SUT.update(1.0));
    ASSERT_TRUE(SUT.get_ready_to_arm().ready_to_arm);
}