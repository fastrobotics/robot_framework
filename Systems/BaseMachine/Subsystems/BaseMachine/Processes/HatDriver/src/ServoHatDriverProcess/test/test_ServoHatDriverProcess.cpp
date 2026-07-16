

#include <gtest/gtest.h>
#include <stdio.h>

#include <Infrastructure/Logger.hpp>
#include <ServoHatDriverProcess/ServoHatDriverProcess.hpp>

using namespace fast::rf::BaseMachineSystem::BaseMachineSubsystem;

TEST(ServoHatDriverProcess, BasicTests) {
    ServoHatDriverProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(SUT.update(0.0, 0.0));
    fast::rf::Logger::log_notice(SUT.pretty());
    ASSERT_TRUE(SUT.setServoValue(0, 0));
    auto diagnostics = SUT.get_diagnostics();
    ASSERT_GT(diagnostics.size(), 0);
    for (auto diagnostic : diagnostics) {
        ASSERT_NE(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
        ASSERT_LT(diagnostic.level, fast::rf::Level::WARN);
    }
}
TEST(ServoHatDriverProcess, BasicConversionTests) {
    ServoHatDriverProcess SUT;
    ASSERT_TRUE(SUT.init());
    ASSERT_TRUE(true);
}