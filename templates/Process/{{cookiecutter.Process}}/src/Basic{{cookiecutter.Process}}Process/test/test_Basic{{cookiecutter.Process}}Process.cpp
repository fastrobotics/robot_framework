

#include <Basic{{cookiecutter.Process}}Process/Basic{{cookiecutter.Process}}Process.hpp>

#include <gtest/gtest.h>
#include <stdio.h>

using namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem::{{cookiecutter.Process}};
#include <Infrastructure/Logger.hpp>

TEST(Basic{{cookiecutter.Process}}Process, BasicTests) {
  Basic{{cookiecutter.Process}}Process sut;
  ASSERT_TRUE(sut.init());
  ASSERT_TRUE(sut.update(0.0));
  auto diagnostics = sut.getDiagnostics();
  ASSERT_GT(diagnostics.size(), 0);
  for (auto diagnostic : diagnostics) {
    ASSERT_NE(diagnostic.diagnosticMessage,fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
    ASSERT_LT(diagnostic.level, fast::rf::Level::WARN);
  }
   ASSERT_TRUE(sut.getReadyToArm().ready_to_arm);
   fast::rf::Logger::logDebug(sut.pretty());
}
TEST(Basic{{cookiecutter.Process}}Process, BasicConversionTests) {
  Basic{{cookiecutter.Process}}Process sut;
  ASSERT_TRUE(sut.init());
  ASSERT_GT(sut.pretty().size(), 0);
}