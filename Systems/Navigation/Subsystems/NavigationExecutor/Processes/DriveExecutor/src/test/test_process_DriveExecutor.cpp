

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseDriveExecutorProcess.hpp>
#include <IDriveExecutorOutput.hpp>
#include <IDriveExecutorProcess.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::DriveExecutor;
class TestDriveExecutorOutput : public IDriveExecutorOutput {
   public:
    int a{1};
};
class TestDriveExecutorProcessInterface : public IDriveExecutorProcess {
   public:
    IDriveExecutorOutput* new_cmd([[maybe_unused]] GeometryMsgs::TwistMsg cmd) override { return output; }

    IDriveExecutorOutput* get_output() { return output; }
    bool init() { return true; }

    bool update([[maybe_unused]] double current_time_sec) override { return false; }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> empty;

        return empty;
    }
    std::string pretty() override { return "Test"; }
    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() {
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;
        return ready_to_arm;
    }

   private:
    TestDriveExecutorOutput* output = new TestDriveExecutorOutput();
};
TEST(TestDriveExecutorProcessInterface, InterfaceTests) {
    TestDriveExecutorProcessInterface SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_EQ(SUT.getDiagnostics().size(), 0);
    ASSERT_FALSE(SUT.update(0.0));
    GeometryMsgs::TwistMsg cmd;
    auto general_output = SUT.new_cmd(cmd);
    ASSERT_NE(general_output, nullptr);

    TestDriveExecutorOutput* output = dynamic_cast<TestDriveExecutorOutput*>(general_output);
    ASSERT_NE(output, nullptr);
    ASSERT_EQ(output->a, 1);

    general_output = SUT.get_output();
    ASSERT_NE(general_output, nullptr);

    output = dynamic_cast<TestDriveExecutorOutput*>(general_output);
    ASSERT_NE(output, nullptr);
    ASSERT_EQ(output->a, 1);
}
class TestBaseDriveExecutorProcess : public BaseDriveExecutorProcess {
   public:
    TestBaseDriveExecutorProcess() : BaseDriveExecutorProcess() {}
    bool init() override {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        bool status = diagnosticManager.initializeDiagnostics(diagnostic_types);
        return status;
    }
    IDriveExecutorOutput* new_cmd([[maybe_unused]] GeometryMsgs::TwistMsg cmd) override { return nullptr; }
    IDriveExecutorOutput* get_output() { return nullptr; }
    bool update(double current_time_sec) override { return BaseDriveExecutorProcess::update(current_time_sec); }
    std::string pretty() {
        std::string str = "---Test-Base---\n";
        str += BaseDriveExecutorProcess::pretty();
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
TEST(BaseDriveExecutorProcess, BasicAssertions) {
    TestBaseDriveExecutorProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.getDiagnostics().size(), 0);
    ASSERT_TRUE(SUT.update(0.0));
    ASSERT_TRUE(SUT.inject_error());
    ASSERT_TRUE(SUT.update(1.0));
    ASSERT_FALSE(SUT.get_ready_to_arm().ready_to_arm);
    ASSERT_TRUE(SUT.clear_error());
    ASSERT_TRUE(SUT.update(1.0));
    ASSERT_TRUE(SUT.get_ready_to_arm().ready_to_arm);
}