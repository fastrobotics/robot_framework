

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseLocalPoseFuserProcess.hpp>
#include <ILocalPoseFuserProcess.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::PoseSystem::LocalPoseSubsystem;
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
}