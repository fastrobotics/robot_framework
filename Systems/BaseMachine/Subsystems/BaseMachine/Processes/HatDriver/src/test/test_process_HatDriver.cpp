

/**
 * @compare_tag Process-BaseSourceTest
 *
 */
#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseHatDriverProcess.hpp>
#include <IHatDriverProcess.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem::HatDriver;
class TestHatDriverProcessInterface : public IHatDriverProcess {
   public:
    bool init() { return true; }
    std::string pretty() { return ""; }
    bool update([[maybe_unused]] double current_time_sec) override { return false; }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> empty;

        return empty;
    }
    void update_RobotArmCommand([
        [maybe_unused]] fast::rf::messages::InfrastructureMsgs::ArmCommandMsg robot_arm_command) {}
    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() {
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;
        return ready_to_arm;
    }
};
TEST(TestHatDriverProcessInterface, InterfaceTests) {
    TestHatDriverProcessInterface SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_EQ(SUT.getDiagnostics().size(), 0);
    ASSERT_FALSE(SUT.update(0.0));
}
class TestBaseHatDriverProcess : public BaseHatDriverProcess {
   public:
    TestBaseHatDriverProcess() : BaseHatDriverProcess() {}
    bool init() override {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        bool status = diagnosticManager.initializeDiagnostics(diagnostic_types);
        return status;
    }
    bool update(double current_time_sec) override { return BaseHatDriverProcess::update(current_time_sec); }
    std::string pretty() {
        std::string str = "---Test-Base---\n";
        str += BaseHatDriverProcess::pretty();
        return str;
    }
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
TEST(BaseHatDriverProcess, BasicAssertions) {
    TestBaseHatDriverProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.getDiagnostics().size(), 0);
    ASSERT_TRUE(SUT.update(0.0));
    ASSERT_GT(SUT.pretty().size(), 0);
    ASSERT_TRUE(SUT.inject_error());
    ASSERT_TRUE(SUT.update(1.0));
    ASSERT_FALSE(SUT.get_ready_to_arm().ready_to_arm);
    ASSERT_TRUE(SUT.clear_error());
    ASSERT_TRUE(SUT.update(1.0));
    ASSERT_TRUE(SUT.get_ready_to_arm().ready_to_arm);
}