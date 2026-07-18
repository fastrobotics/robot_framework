

#include <gtest/gtest.h>
#include <stdio.h>

#include <ArmedStateManagerProcess.hpp>
#include <BaseArmedStateManagerProcess.hpp>
#include <IArmedStateManagerProcess.hpp>
#include <Infrastructure/Logger.hpp>

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
    fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse request_armstate_change([
        [maybe_unused]] fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse request)
        override {
        fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse response;
        response.request_approved = false;
        return response;
    }

    bool new_ReadyToArmStatus([
        [maybe_unused]] fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg msg) override {
        return false;
    }

    fast::rf::messages::InfrastructureMsgs::ArmCommandMsg get_ArmCommandMsg() {
        fast::rf::messages::InfrastructureMsgs::ArmCommandMsg arm_command;
        return arm_command;
    }
};
TEST(TestArmedStateManagerProcessInterface, InterfaceTests) {
    TestArmedStateManagerProcessInterface SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_EQ(SUT.get_diagnostics().size(), 0);
    ASSERT_FALSE(SUT.update(0.0, 0.0));
    fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse request;
    auto response = SUT.request_armstate_change(request);
    ASSERT_FALSE(response.request_approved);
    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm_msg;
    ASSERT_FALSE(SUT.new_ReadyToArmStatus(ready_to_arm_msg));
    ASSERT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::UNKNOWN);
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
    fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse request_armstate_change([
        [maybe_unused]] fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse request)
        override {
        fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse response;
        response.request_approved = false;
        return response;
    }

    bool new_ReadyToArmStatus([
        [maybe_unused]] fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg msg) override {
        return false;
    }
};
TEST(BaseArmedStateManagerProcess, BasicAssertions) {
    TestBaseArmedStateManagerProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_GT(SUT.get_diagnostics().size(), 0);
    ASSERT_TRUE(SUT.update(0.0, 0.0));
    fast::rf::messages::InfrastructureMsgs::ArmStateChangeSrv::ArmStateChangeSrvResponse request;
    auto response = SUT.request_armstate_change(request);
    ASSERT_FALSE(response.request_approved);
    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm_msg;
    ASSERT_FALSE(SUT.new_ReadyToArmStatus(ready_to_arm_msg));
    ASSERT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::UNKNOWN);
}
TEST(ArmedStateManagerProcess, BasicTests) {
    ArmedStateManagerProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0, 0.0));
    auto diagnostics = SUT.get_diagnostics();
    ASSERT_GT(diagnostics.size(), 0);
    fast::rf::Logger::log_info(SUT.pretty());

    EXPECT_EQ(SUT.get_ArmCommandMsg().armed_state, fast::rf::ArmedState::ARMED);
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