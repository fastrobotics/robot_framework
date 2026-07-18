
#include <gtest/gtest.h>
#include <stdio.h>

#include <Infrastructure/Logger.hpp>
#include <ReadyToArmComputer.hpp>
#include <ReadyToArmStatusMsg.hpp>
using namespace fast::rf::SafetySystem::ModeManagerSubsystem;
TEST(ReadyToArmComputer, InterfaceTests) {
    ReadyToArmComputer SUT;
    ASSERT_TRUE(SUT.add_monitor(1, 2, 3));
    ASSERT_TRUE(SUT.init());
    auto str = SUT.pretty();
    ASSERT_GT(str.size(), 0);
    fast::rf::Logger::log_debug(SUT.pretty());
    ASSERT_TRUE(SUT.update(0.0));
}
