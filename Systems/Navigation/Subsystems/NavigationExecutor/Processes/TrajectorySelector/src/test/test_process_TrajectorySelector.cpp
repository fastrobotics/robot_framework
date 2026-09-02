/**
 * @compare_tag Process-BaseSourceTest v0.1
 *
 */
#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseTrajectorySelectorProcess.hpp>
#include <ITrajectorySelectorProcess.hpp>

using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectorySelector;
class TestTrajectorySelectorProcessInterface : public ITrajectorySelectorProcess {
   public:
    bool init() { return true; }
    uint8_t getSystemId() override { return 0; }
    uint8_t getSubSystemId() override { return 0; }
    uint8_t getProcessId() override { return 0; }
    bool updateDiagnostic([[maybe_unused]] fast::rf::DiagnosticDefinition::DiagnosticType type,
                          [[maybe_unused]] fast::rf::Level level,
                          [[maybe_unused]] fast::rf::DiagnosticDefinition::DiagnosticMessage message,
                          [[maybe_unused]] std::string description) override {
        return false;
    }
    bool update([[maybe_unused]] double current_time_sec) override { return false; }
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
TEST(TestTrajectorySelectorProcessInterface, InterfaceTests) {
    TestTrajectorySelectorProcessInterface SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_EQ(SUT.getDiagnostics().size(), 0);
    ASSERT_FALSE(SUT.update(0.0));
}
class TestBaseTrajectorySelectorProcess : public BaseTrajectorySelectorProcess {
   public:
    TestBaseTrajectorySelectorProcess() : BaseTrajectorySelectorProcess() {}
    bool init() override {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        bool status = m_diagnosticManager.initializeDiagnostics(diagnostic_types);
        return status;
    }
    bool update(double currentTimeSec) override { return BaseTrajectorySelectorProcess::update(currentTimeSec); }
    std::string pretty() { return BaseTrajectorySelectorProcess::pretty(); }
};
TEST(BaseTrajectorySelectorProcess, BasicAssertions) {
    TestBaseTrajectorySelectorProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.getDiagnostics().size(), 0);
    ASSERT_TRUE(SUT.update(0.0));
}
