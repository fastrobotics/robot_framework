

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseTrajectoryControllerProcess.hpp>
#include <Controller/PIDController/PIDController.hpp>
#include <ITrajectoryControllerProcess.hpp>

using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem;
class TestTrajectoryControllerProcessInterface : public ITrajectoryControllerProcess {
   public:
    bool init() override { return true; }
    bool update([[maybe_unused]] double current_time_sec) override { return false; }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> empty;

        return empty;
    }
    bool new_pose([[maybe_unused]] fast::rf::messages::GeometryMsgs::OdomMsg pose) { return false; }
    bool new_desired_command([[maybe_unused]] fast::rf::messages::GeometryMsgs::TwistMsg cmd) { return false; }
    bool get_command([[maybe_unused]] fast::rf::messages::GeometryMsgs::TwistMsg& cmd) { return false; }
};
TEST(TestTrajectoryControllerProcessInterface, InterfaceTests) {
    TestTrajectoryControllerProcessInterface SUT;
    ASSERT_FALSE(SUT.update(0.0));
}
class TestBaseTrajectoryControllerProcess : public BaseTrajectoryControllerProcess {
   public:
    TestBaseTrajectoryControllerProcess() : BaseTrajectoryControllerProcess() {}
    bool init() override {
        controller = new fast::rf::NavigationSystem::Controller::PIDController;
        bool status = BaseTrajectoryControllerProcess::init();
        if (status == false) {
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
    bool update(double current_time_sec) override { return BaseTrajectoryControllerProcess::update(current_time_sec); }
    bool new_pose(fast::rf::messages::GeometryMsgs::OdomMsg pose) {
        return BaseTrajectoryControllerProcess::new_pose(pose);
    }
    bool new_desired_command(fast::rf::messages::GeometryMsgs::TwistMsg cmd) {
        return BaseTrajectoryControllerProcess::new_desired_command(cmd);
    }
};
TEST(BaseTrajectoryControllerProcess, BasicAssertions) {
    TestBaseTrajectoryControllerProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.get_diagnostics().size(), 0);
    ASSERT_TRUE(SUT.update(0.0));
}