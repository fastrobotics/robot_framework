

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseLocalPoseFuserProcess.hpp>
#include <ILocalPoseFuserProcess.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::PoseSystem::LocalPoseSubsystem::LocalPoseFuser;
class TestLocalPoseFuserProcessInterface : public ILocalPoseFuserProcess {
   public:
    bool init() { return true; }
    bool update([[maybe_unused]] double current_time_sec) override { return false; }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> empty;

        return empty;
    }
    std::string pretty() override { return ""; }
    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() {
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;
        return ready_to_arm;
    }
    bool new_machine_inertial_data([[maybe_unused]] fast::rf::messages::SensorMsgs::ImuMsg machine_inertial_data) {
        return false;
    }

    bool get_local_pose([[maybe_unused]] fast::rf::messages::GeometryMsgs::OdomMsg& local_pose,
                        [[maybe_unused]] fast::rf::messages::GeometryMsgs::AccelWithCovarianceMsg& angular_acc) {
        return false;
    }
};
TEST(TestLocalPoseFuserProcessInterface, InterfaceTests) {
    TestLocalPoseFuserProcessInterface SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_EQ(SUT.get_diagnostics().size(), 0);
    ASSERT_FALSE(SUT.update(0.0));
}
class TestBaseLocalPoseFuserProcess : public BaseLocalPoseFuserProcess {
   public:
    TestBaseLocalPoseFuserProcess() : BaseLocalPoseFuserProcess() {}
    bool init() override {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
    bool update(double current_time_sec) override { return BaseLocalPoseFuserProcess::update(current_time_sec); }
    std::string pretty() {
        std::string str = "---Test-Base---\n";
        str += BaseLocalPoseFuserProcess::pretty();
        return str;
    }
    bool inject_error() {
        return diagnosticManager.update_diagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::ERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::DIAGNOSTIC_FAILED, "Testing Error Injection");
    }
    bool clear_error() {
        return diagnosticManager.update_diagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::NOERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Clearing Error Injection");
    }
    bool new_machine_inertial_data([[maybe_unused]] fast::rf::messages::SensorMsgs::ImuMsg machine_inertial_data) {
        fast::rf::messages::GeometryMsgs::OdomMsg pose;
        fast::rf::messages::GeometryMsgs::AccelWithCovarianceMsg angular_acc;
        new_local_pose(pose, angular_acc);
        return true;
    }
};
TEST(BaseLocalPoseFuserProcess, BasicAssertions) {
    TestBaseLocalPoseFuserProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.get_diagnostics().size(), 0);
    ASSERT_TRUE(SUT.update(0.0));
    ASSERT_TRUE(SUT.inject_error());
    ASSERT_TRUE(SUT.update(1.0));
    ASSERT_FALSE(SUT.get_ready_to_arm().ready_to_arm);
    ASSERT_TRUE(SUT.clear_error());
    ASSERT_TRUE(SUT.update(1.0));
    ASSERT_TRUE(SUT.get_ready_to_arm().ready_to_arm);

    fast::rf::Logger::logDebug(SUT.pretty());
    fast::rf::messages::SensorMsgs::ImuMsg machine_inertial_data;
    ASSERT_TRUE(SUT.new_machine_inertial_data(machine_inertial_data));
    fast::rf::Logger::logDebug(SUT.pretty());
    fast::rf::messages::GeometryMsgs::OdomMsg local_pose;
    fast::rf::messages::GeometryMsgs::AccelWithCovarianceMsg local_pose_angular_acc;
    ASSERT_TRUE(SUT.get_local_pose(local_pose, local_pose_angular_acc));
    fast::rf::Logger::logDebug(SUT.pretty());
    ASSERT_FALSE(SUT.get_local_pose(local_pose, local_pose_angular_acc));
    fast::rf::Logger::logDebug(SUT.pretty());
}