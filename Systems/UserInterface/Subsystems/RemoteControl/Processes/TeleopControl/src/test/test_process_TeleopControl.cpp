

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseTeleopControlProcess.hpp>
#include <ITeleopControlProcess.hpp>

using namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem;
class TestTeleopControlProcessInterface : public ITeleopControlProcess {
   public:
    bool init() { return true; }
    bool update([[maybe_unused]] double current_time_sec, [[maybe_unused]] double delta_time_sec) override {
        return false;
    }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> empty;

        return empty;
    }
    std::string pretty() { return "Test"; }
};
TEST(TestTeleopControlProcessInterface, InterfaceTests) {
    TestTeleopControlProcessInterface SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_EQ(SUT.get_diagnostics().size(), 0);
    ASSERT_FALSE(SUT.update(0.0, 0.0));
}
class TestBaseTeleopControlProcess : public BaseTeleopControlProcess {
   public:
    TestBaseTeleopControlProcess() : BaseTeleopControlProcess() {}
    bool init() override {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
    bool update([[maybe_unused]] double current_time_sec, [[maybe_unused]] double delta_time_sec) override {
        return base_update(current_time_sec, delta_time_sec);
    }
};
TEST(BaseTeleopControlProcess, BasicAssertions) {
    TestBaseTeleopControlProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.get_diagnostics().size(), 0);
    ASSERT_TRUE(SUT.update(0.0, 0.0));
    printf("%s\n", SUT.pretty().c_str());
}