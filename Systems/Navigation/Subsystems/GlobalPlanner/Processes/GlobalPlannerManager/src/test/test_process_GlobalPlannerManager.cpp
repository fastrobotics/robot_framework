

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseGlobalPlannerManagerProcess.hpp>
#include <IGlobalPlannerManagerProcess.hpp>

using namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem::GlobalPlannerManager;
class TestGlobalPlannerManagerProcessInterface : public IGlobalPlannerManagerProcess {
   public:
    bool init() { return true; }
    bool update([[maybe_unused]] double current_time_sec) override { return false; }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> empty;

        return empty;
    }
};
TEST(TestGlobalPlannerManagerProcessInterface, InterfaceTests) {
    TestGlobalPlannerManagerProcessInterface SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_EQ(SUT.getDiagnostics().size(), 0);
    ASSERT_FALSE(SUT.update(0.0));
}
class TestBaseGlobalPlannerManagerProcess : public BaseGlobalPlannerManagerProcess {
   public:
    TestBaseGlobalPlannerManagerProcess() : BaseGlobalPlannerManagerProcess() {}
    bool init() override {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        bool status = diagnosticManager.initializeDiagnostics(diagnostic_types);
        return status;
    }
    bool update(double current_time_sec) override { return base_update(current_time_sec); }
};
TEST(BaseGlobalPlannerManagerProcess, BasicAssertions) {
    TestBaseGlobalPlannerManagerProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.getDiagnostics().size(), 0);
    ASSERT_TRUE(SUT.update(0.0));
}
