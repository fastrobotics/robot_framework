

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseDriveExecutorProcess.hpp>
#include <IDriveExecutorOutput.hpp>
#include <IDriveExecutorProcess.hpp>

using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem;
class TestDriveExecutorOutput : public IDriveExecutorOutput {
   public:
    int a{1};
};
class TestDriveExecutorProcessInterface : public IDriveExecutorProcess {
   public:
    IDriveExecutorOutput* new_cmd(GeometryMsgs::TwistMsg cmd) override { return output; }
    bool init() { return true; }

    bool update(double current_time_sec, [[maybe_unused]] double delta_time_sec) override { return false; }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() { return diagnostics; }

   private:
    TestDriveExecutorOutput* output = new TestDriveExecutorOutput();
    fast::rf::messages::InfrastructureMsgs::DiagnosticMsg root_diagnostic;
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> diagnostics;
};
TEST(TestDriveExecutorProcessInterface, InterfaceTests) {
    TestDriveExecutorProcessInterface SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_EQ(SUT.get_diagnostics().size(), 0);
    ASSERT_FALSE(SUT.update(0.0, 0.0));
    GeometryMsgs::TwistMsg cmd;
    auto general_output = SUT.new_cmd(cmd);
    ASSERT_NE(general_output, nullptr);

    TestDriveExecutorOutput* output = dynamic_cast<TestDriveExecutorOutput*>(general_output);
    ASSERT_NE(output, nullptr);
    ASSERT_EQ(output->a, 1);
}
class TestBaseDriveExecutorProcess : public BaseDriveExecutorProcess {
   public:
    TestBaseDriveExecutorProcess() : BaseDriveExecutorProcess() {}
    bool init() override {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        return initialize_diagnostics(diagnostic_types);
    }
    IDriveExecutorOutput* new_cmd(GeometryMsgs::TwistMsg cmd) override { return nullptr; }
    bool update(double current_time_sec, [[maybe_unused]] double delta_time_sec) override {
        return base_update(current_time_sec, delta_time_sec);
    }
};
TEST(BaseDriveExecutorProcess, BasicAssertions) {
    TestBaseDriveExecutorProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.get_diagnostics().size(), 0);
    ASSERT_TRUE(SUT.update(0.0, 0.0));
}