

#include <gtest/gtest.h>
#include <stdio.h>

#include <ArmedStateManagerProcess.hpp>
#include <BaseArmedStateManagerProcess.hpp>
#include <IArmedStateManagerProcess.hpp>

using namespace fast::rf::SafetySystem::ModeManagerSubsystem;
class TestArmedStateManagerProcessInterface : public IArmedStateManagerProcess {
   public:
    bool init() { return true; }
    bool update([[maybe_unused]] double current_time_sec, [[maybe_unused]] double delta_time_sec) override {
        return false;
    }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> empty;

        return empty;
    }
    std::string pretty() override { return ""; }
};
TEST(TestArmedStateManagerProcessInterface, InterfaceTests) {
    TestArmedStateManagerProcessInterface SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_EQ(SUT.get_diagnostics().size(), 0);
    ASSERT_FALSE(SUT.update(0.0, 0.0));
}
class TestBaseArmedStateManagerProcess : public BaseArmedStateManagerProcess {
   public:
    TestBaseArmedStateManagerProcess() : BaseArmedStateManagerProcess() {}
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
TEST(BaseArmedStateManagerProcess, BasicAssertions) {
    TestBaseArmedStateManagerProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.get_diagnostics().size(), 0);
    ASSERT_TRUE(SUT.update(0.0, 0.0));
}
TEST(ArmedStateManagerProcess, BasicTests) {
    ArmedStateManagerProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0, 0.0));
    auto diagnostics = SUT.get_diagnostics();
    ASSERT_GT(diagnostics.size(), 0);
    /**
     * @todo Implement this during AB#1766
     */
    /*
    for (auto diagnostic : diagnostics) {
        ASSERT_NE(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
        ASSERT_LT(diagnostic.level, fast::rf::Level::WARN);
    }
    */
}