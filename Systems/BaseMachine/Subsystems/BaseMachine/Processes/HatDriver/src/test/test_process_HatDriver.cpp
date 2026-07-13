

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseHatDriverProcess.hpp>
#include <IHatDriverProcess.hpp>

using namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem;
class TestHatDriverProcessInterface : public IHatDriverProcess {
   public:
    bool init() { return true; }
    std::string pretty() { return ""; }
    bool update([[maybe_unused]] double current_time_sec, [[maybe_unused]] double delta_time_sec) override {
        return false;
    }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> empty;

        return empty;
    }
};
TEST(TestHatDriverProcessInterface, InterfaceTests) {
    TestHatDriverProcessInterface SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_EQ(SUT.get_diagnostics().size(), 0);
    ASSERT_FALSE(SUT.update(0.0, 0.0));
}
class TestBaseHatDriverProcess : public BaseHatDriverProcess {
   public:
    TestBaseHatDriverProcess() : BaseHatDriverProcess() {}
    bool init() override {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
    bool update([[maybe_unused]] double current_time_sec, [[maybe_unused]] double delta_time_sec) override {
        return base_update(current_time_sec, delta_time_sec);
    }
    std::string pretty() {
        std::string str = "---Test-Base---\n";
        str += base_pretty();
        return str;
    }
};
TEST(BaseHatDriverProcess, BasicAssertions) {
    TestBaseHatDriverProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.get_diagnostics().size(), 0);
    ASSERT_TRUE(SUT.update(0.0, 0.0));
    ASSERT_GT(SUT.pretty().size(), 0);
}