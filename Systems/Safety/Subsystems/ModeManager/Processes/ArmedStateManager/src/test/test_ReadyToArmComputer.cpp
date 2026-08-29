
#include <gtest/gtest.h>
#include <stdio.h>

#include <Infrastructure/Logger.hpp>
#include <ReadyToArmComputer.hpp>
#include <ReadyToArmStatusMsg.hpp>
using namespace fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager;
TEST(ReadyToArmComputer, InterfaceTests) {
    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg process1;
    process1.systemID = 1;
    process1.subsystemID = 2;
    process1.processID = 3;
    process1.ready_to_arm = false;
    ReadyToArmComputer SUT;
    EXPECT_FALSE(SUT.get_ready_to_arm());
    ASSERT_FALSE(SUT.update(0.0));
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.set_config(1));
    ASSERT_TRUE(SUT.update(1.0));
    auto str = SUT.pretty();
    ASSERT_GT(str.size(), 0);
    fast::rf::Logger::logDebug("\n" + SUT.pretty());
    ASSERT_TRUE(SUT.update(2.0));

    ASSERT_TRUE(SUT.new_ArmedStatus(process1));
    ASSERT_FALSE(SUT.get_ready_to_arm());
    fast::rf::Logger::logDebug("\n" + SUT.pretty());
    process1.ready_to_arm = true;
    ASSERT_TRUE(SUT.new_ArmedStatus(process1));
    ASSERT_TRUE(SUT.update(2.1));
    ASSERT_TRUE(SUT.get_ready_to_arm());

    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg processX;
    ASSERT_FALSE(SUT.new_ArmedStatus(processX));
    ASSERT_TRUE(SUT.update(2.2));
    ASSERT_TRUE(SUT.get_ready_to_arm());

    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg process2;
    process2.systemID = process1.subsystemID + 1;
    process2.subsystemID = 3;
    process2.processID = 3;
    process2.ready_to_arm = true;
    ASSERT_TRUE(SUT.new_ArmedStatus(process2));  // Unexpected Ready To Arm Signal.  But if it was directed to this
                                                 // module, we should go ahead and use it.
    ASSERT_TRUE(SUT.update(2.3));
    ASSERT_TRUE(SUT.get_ready_to_arm());
    fast::rf::Logger::logDebug("\n" + SUT.pretty());
}
TEST(ReadyToArmComputer, FailureTests) {
    ReadyToArmComputer SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_FALSE(SUT.set_config(0));
}
TEST(ReadyToArmComputer, FullTests) {
    double current_time = 0.0;
    ReadyToArmComputer SUT;
    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg process1;
    process1.systemID = 1;
    process1.subsystemID = 2;
    process1.processID = 3;

    fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg process2;
    process2.systemID = 2;
    process2.subsystemID = 3;
    process2.processID = 4;
    ASSERT_FALSE(SUT.is_all_signals_ever_received());
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.set_config(2));
    ASSERT_TRUE(SUT.update(current_time));
    ASSERT_FALSE(SUT.is_all_signals_ever_received());
    process1.ready_to_arm = true;
    ASSERT_TRUE(SUT.new_ArmedStatus(process1));
    ASSERT_FALSE(SUT.is_all_signals_ever_received());
    process2.ready_to_arm = true;
    ASSERT_TRUE(SUT.new_ArmedStatus(process2));
    current_time += 0.1;
    ASSERT_TRUE(SUT.update(current_time));
    ASSERT_TRUE(SUT.is_all_signals_ever_received());

    ASSERT_TRUE(SUT.get_ready_to_arm());
    ASSERT_TRUE(SUT.is_all_signals_ever_received());
    ASSERT_TRUE(SUT.is_all_signals_rate_ok());

    current_time += ReadyToArmComputer::PROCESS_TIMEOUT_SEC / 2.0;
    ASSERT_TRUE(SUT.update(current_time));
    ASSERT_TRUE(SUT.get_ready_to_arm());

    current_time += 1.0 + ReadyToArmComputer::PROCESS_TIMEOUT_SEC / 2.0;
    ASSERT_TRUE(SUT.update(current_time));
    fast::rf::Logger::logInfo(SUT.pretty());
    ASSERT_FALSE(SUT.get_ready_to_arm());
    ASSERT_FALSE(SUT.is_all_signals_rate_ok());

    process1.ready_to_arm = true;
    ASSERT_TRUE(SUT.new_ArmedStatus(process1));
    current_time += 0.1;
    ASSERT_TRUE(SUT.update(current_time));
    ASSERT_FALSE(SUT.get_ready_to_arm());
    ASSERT_FALSE(SUT.is_all_signals_rate_ok());

    process2.ready_to_arm = true;
    ASSERT_TRUE(SUT.new_ArmedStatus(process2));
    current_time += 0.1;
    ASSERT_TRUE(SUT.update(current_time));
    fast::rf::Logger::logInfo(SUT.pretty());
    ASSERT_TRUE(SUT.get_ready_to_arm());
    ASSERT_TRUE(SUT.is_all_signals_rate_ok());

    process2.ready_to_arm = false;
    ASSERT_TRUE(SUT.new_ArmedStatus(process2));
    current_time += 0.1;
    ASSERT_TRUE(SUT.update(current_time));
    fast::rf::Logger::logInfo(SUT.pretty());
    ASSERT_FALSE(SUT.get_ready_to_arm());

    process2.ready_to_arm = true;
    ASSERT_TRUE(SUT.new_ArmedStatus(process2));
    current_time += 0.1;
    ASSERT_TRUE(SUT.update(current_time));
    fast::rf::Logger::logInfo(SUT.pretty());
    ASSERT_TRUE(SUT.get_ready_to_arm());
}