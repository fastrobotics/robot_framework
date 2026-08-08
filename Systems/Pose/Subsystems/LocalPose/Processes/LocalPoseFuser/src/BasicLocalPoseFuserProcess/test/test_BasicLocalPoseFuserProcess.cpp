

#include <BasicLocalPoseFuserProcess/BasicLocalPoseFuserProcess.hpp>

#include <gtest/gtest.h>
#include <stdio.h>

using namespace fast::rf::PoseSystem::LocalPoseSubsystem;

TEST(BasicLocalPoseFuserProcess, BasicTests) {
  BasicLocalPoseFuserProcess SUT;
  ASSERT_TRUE(SUT.init());
  ASSERT_TRUE(SUT.update(0.0));
  auto diagnostics = SUT.get_diagnostics();
  ASSERT_GT(diagnostics.size(), 0);
  for (auto diagnostic : diagnostics) {
    ASSERT_NE(diagnostic.diagnosticMessage,fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
    ASSERT_LT(diagnostic.level, fast::rf::Level::WARN);
  }
   ASSERT_TRUE(SUT.get_ready_to_arm().ready_to_arm);
}
TEST(BasicLocalPoseFuserProcess, BasicConversionTests) {
  BasicLocalPoseFuserProcess SUT;
  ASSERT_TRUE(SUT.init());
  ASSERT_GT(SUT.pretty().size(), 0);
}