
#include <gtest/gtest.h>

#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <RobotFrameworkDefinitions.hpp>
using namespace fast::rf::core::infrastructure;
TEST(DiagnosticManager, BasicAssertions) {
    DiagnosticManager SUT(1, 2, 3);
    std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
    diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
    ASSERT_TRUE(SUT.initialize_diagnostics(diagnostic_types));
    ASSERT_TRUE(SUT.is_initialized());
    ASSERT_GT(SUT.get_diagnostics().size(), 0);
    for (auto diagnostic : SUT.get_diagnostics()) {
        ASSERT_EQ(diagnostic.systemID, 1);
        ASSERT_EQ(diagnostic.subsystemID, 2);
        ASSERT_EQ(diagnostic.processID, 3);
        ASSERT_EQ(diagnostic.diagnosticType, fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        ASSERT_EQ(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
        ASSERT_EQ(diagnostic.level, fast::rf::Level::INFO);
        ASSERT_NE(diagnostic.description, "");
    }
}
TEST(DiagnosticManager, ImproperConstruction) {
    {
        DiagnosticManager SUT(0, 1, 2);
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        EXPECT_FALSE(SUT.initialize_diagnostics(diagnostic_types));
        EXPECT_FALSE(SUT.is_initialized());
        EXPECT_EQ(SUT.get_diagnostics().size(), 0);
    }
    {
        DiagnosticManager SUT(1, 0, 2);
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        EXPECT_FALSE(SUT.initialize_diagnostics(diagnostic_types));
        EXPECT_FALSE(SUT.is_initialized());
        EXPECT_EQ(SUT.get_diagnostics().size(), 0);
    }
    {
        DiagnosticManager SUT(1, 2, 0);
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        EXPECT_FALSE(SUT.initialize_diagnostics(diagnostic_types));
        EXPECT_FALSE(SUT.is_initialized());
        EXPECT_EQ(SUT.get_diagnostics().size(), 0);
    }
}
TEST(DiagnosticManager, Printing) {
    DiagnosticManager SUT(1, 2, 3);
    std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
    diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
    diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::COMMUNICATIONS);
    diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::PLANNING);
    ASSERT_TRUE(SUT.initialize_diagnostics(diagnostic_types));
    ASSERT_TRUE(SUT.is_initialized());
    ASSERT_EQ(SUT.get_diagnostics().size(), 3);
    std::string str = SUT.pretty();
    ASSERT_GT(str.size(), 0);
    printf("%s", str.c_str());
}