/**
 * @compare_tag Process-BasicSourceTest v0.1
 * 
 */

#include <Basic{{cookiecutter.Process}}Process/Basic{{cookiecutter.Process}}Process.hpp>

#include <gtest/gtest.h>
#include <stdio.h>

using namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem::{{cookiecutter.Process}};
#include <Infrastructure/Logger.hpp>

TEST(Basic{{cookiecutter.Process}}Process, BasicTests) {
  Basic{{cookiecutter.Process}}Process SUT;
  ASSERT_TRUE(SUT.init());
  ASSERT_TRUE(SUT.update(0.0));
  auto diagnostics = SUT.getDiagnostics();
  ASSERT_GT(diagnostics.size(), 0);
  for (auto diagnostic : diagnostics) {
    ASSERT_NE(diagnostic.diagnosticMessage,fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
    ASSERT_LT(diagnostic.level, fast::rf::Level::WARN);
  }
   ASSERT_TRUE(SUT.getReadyToArm().ready_to_arm);
   fast::rf::Logger::logDebug(SUT.pretty());
}
TEST(Basic{{cookiecutter.Process}}Process, BasicConversionTests) {
  Basic{{cookiecutter.Process}}Process SUT;
  ASSERT_TRUE(SUT.init());
  ASSERT_GT(SUT.pretty().size(), 0);
}
