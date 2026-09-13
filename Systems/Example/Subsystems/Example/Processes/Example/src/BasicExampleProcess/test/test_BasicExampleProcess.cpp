/**
 * @compare_tag Process-BasicSourceTest v0.1
 *
 */

#include <gtest/gtest.h>
#include <stdio.h>

#include <BasicExampleProcess/BasicExampleProcess.hpp>

using namespace fast::rf::ExampleSystem::ExampleSubsystem::Example;
#include <Infrastructure/Logger.hpp>

TEST(BasicExampleProcess, BasicTests) {
    BasicExampleProcess sut;
    ASSERT_TRUE(sut.init());
    ASSERT_TRUE(sut.update(0.0));
    auto diagnostics = sut.getDiagnostics();
    ASSERT_GT(diagnostics.size(), 0);
    for (auto diagnostic : diagnostics) {
        ASSERT_NE(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
        ASSERT_LT(diagnostic.level, fast::rf::Level::WARN);
    }
    ASSERT_TRUE(sut.get_ready_to_arm().ready_to_arm);
    fast::rf::Logger::logDebug(sut.pretty());
}
TEST(BasicExampleProcess, BasicConversionTests) {
    BasicExampleProcess sut;
    ASSERT_TRUE(sut.init());
    ASSERT_GT(sut.pretty().size(), 0);
}
