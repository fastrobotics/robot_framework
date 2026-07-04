

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseTrajectorySelectorProcess.hpp>
#include <ITrajectorySelectorProcess.hpp>

using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem;
class TestTrajectorySelectorProcessInterface : public ITrajectorySelectorProcess {
   public:
    bool init() { return true; }
    bool update(double current_time_sec, [[maybe_unused]] double delta_time_sec) override { return false; }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> empty;

        return empty;
    }
};
TEST(TestTrajectorySelectorProcessInterface, InterfaceTests) {
    TestTrajectorySelectorProcessInterface SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_EQ(SUT.get_diagnostics().size(), 0);
    ASSERT_FALSE(SUT.update(0.0, 0.0));
}
class TestBaseTrajectorySelectorProcess : public BaseTrajectorySelectorProcess {
   public:
    TestBaseTrajectorySelectorProcess() : BaseTrajectorySelectorProcess() {}
    bool init() override {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
    bool update(double current_time_sec, [[maybe_unused]] double delta_time_sec) override {
        return base_update(current_time_sec, delta_time_sec);
    }
};
TEST(BaseTrajectorySelectorProcess, BasicAssertions) {
    TestBaseTrajectorySelectorProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.get_diagnostics().size(), 0);
    ASSERT_TRUE(SUT.update(0.0, 0.0));
}