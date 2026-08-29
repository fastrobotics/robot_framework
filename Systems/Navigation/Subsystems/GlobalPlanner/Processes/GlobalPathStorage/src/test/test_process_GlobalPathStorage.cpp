

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseGlobalPathStorageProcess.hpp>
#include <IGlobalPathStorageProcess.hpp>

using namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem::GlobalPathStorage;
class TestGlobalPathStorageProcessInterface : public IGlobalPathStorageProcess {
   public:
    bool init() { return true; }
    bool update([[maybe_unused]] double current_time_sec) override { return false; }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> empty;

        return empty;
    }
};
TEST(TestGlobalPathStorageProcessInterface, InterfaceTests) {
    TestGlobalPathStorageProcessInterface SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_EQ(SUT.getDiagnostics().size(), 0);
    ASSERT_FALSE(SUT.update(0.0));
}
class TestBaseGlobalPathStorageProcess : public BaseGlobalPathStorageProcess {
   public:
    TestBaseGlobalPathStorageProcess() : BaseGlobalPathStorageProcess() {}
    bool init() override {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        bool status = diagnosticManager.initializeDiagnostics(diagnostic_types);
        return status;
    }
    bool update(double current_time_sec) override { return base_update(current_time_sec); }
};
TEST(BaseGlobalPathStorageProcess, BasicAssertions) {
    TestBaseGlobalPathStorageProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.getDiagnostics().size(), 0);
    ASSERT_TRUE(SUT.update(0.0));
}