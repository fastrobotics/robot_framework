/**
 * @compare_tag Process-BaseSourceTest v0.1
 *
 */
#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseObjectManagerProcess.hpp>
#include <IObjectManagerProcess.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::PerceptionSystem::ObjectTrackerSubsystem::ObjectManager;
class TestObjectManagerProcessInterface : public IObjectManagerProcess {
   public:
    bool init() { return true; }
    bool update([[maybe_unused]] double current_time_sec) override { return false; }
    uint8_t getSystemId() override { return 0; }
    uint8_t getSubSystemId() override { return 0; }
    uint8_t getProcessId() override { return 0; }
    bool updateDiagnostic([[maybe_unused]] fast::rf::DiagnosticDefinition::DiagnosticType type,
                          [[maybe_unused]] fast::rf::Level level,
                          [[maybe_unused]] fast::rf::DiagnosticDefinition::DiagnosticMessage message,
                          [[maybe_unused]] std::string description) override {
        return false;
    }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> empty;

        return empty;
    }
    std::string pretty() override { return ""; }
    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() {
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;
        return ready_to_arm;
    }
};
TEST(TestObjectManagerProcessInterface, InterfaceTests) {
    TestObjectManagerProcessInterface SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_EQ(SUT.getDiagnostics().size(), 0);
    ASSERT_FALSE(SUT.update(0.0));
}
class TestBaseObjectManagerProcess : public BaseObjectManagerProcess {
   public:
    TestBaseObjectManagerProcess() : BaseObjectManagerProcess() {}
    bool init() override {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        bool status = m_diagnosticManager.initializeDiagnostics(diagnostic_types);
        return status;
    }
    bool update(double current_time_sec) override { return BaseObjectManagerProcess::update(current_time_sec); }
    std::string pretty() {
        std::string str = "---Test-Base---\n";
        str += BaseObjectManagerProcess::pretty();
        return str;
    }
    bool inject_error() {
        return m_diagnosticManager.updateDiagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::ERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::DIAGNOSTIC_FAILED, "Testing Error Injection");
    }
    bool clear_error() {
        return m_diagnosticManager.updateDiagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::NOERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Clearing Error Injection");
    }
};
TEST(BaseObjectManagerProcess, BasicAssertions) {
    TestBaseObjectManagerProcess SUT;
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
