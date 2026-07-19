
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
TEST(DiagnosticManager, FullDataAssertions) {
    DiagnosticManager SUT(1, 2, 3);
    std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
    for (uint8_t i = 1; i < (uint8_t)fast::rf::DiagnosticDefinition::DiagnosticType::END_OF_LIST; ++i) {
        diagnostic_types.push_back((fast::rf::DiagnosticDefinition::DiagnosticType)i);
    }

    ASSERT_TRUE(SUT.initialize_diagnostics(diagnostic_types));
    ASSERT_TRUE(SUT.is_initialized());
    ASSERT_GT(SUT.get_diagnostics().size(), 0);
    for (auto diagnostic : SUT.get_diagnostics()) {
        ASSERT_EQ(diagnostic.systemID, 1);
        ASSERT_EQ(diagnostic.subsystemID, 2);
        ASSERT_EQ(diagnostic.processID, 3);
        ASSERT_NE(diagnostic.diagnosticType, fast::rf::DiagnosticDefinition::DiagnosticType::UNKNOWN);
        ASSERT_NE(diagnostic.diagnosticType, fast::rf::DiagnosticDefinition::DiagnosticType::END_OF_LIST);
        ASSERT_EQ(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
        ASSERT_EQ(diagnostic.level, fast::rf::Level::INFO);
        ASSERT_NE(diagnostic.description, "");
    }
    printf("%s\n", SUT.pretty().c_str());

    for (uint8_t i = 1; i < (uint8_t)fast::rf::DiagnosticDefinition::DiagnosticMessage::END_OF_LIST; ++i) {
        ASSERT_TRUE(SUT.update_diagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE,
                                          fast::rf::Level::DEBUG, (fast::rf::DiagnosticDefinition::DiagnosticMessage)i,
                                          "Testing this..."));
        printf("%s\n", SUT.pretty().c_str());
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
TEST(DiagnosticManager, UpdateDiagnostic) {
    DiagnosticManager SUT(1, 2, 3);
    std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
    diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
    diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::COMMUNICATIONS);
    diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::PLANNING);
    ASSERT_TRUE(SUT.initialize_diagnostics(diagnostic_types));
    ASSERT_TRUE(SUT.is_initialized());
    ASSERT_EQ(SUT.get_diagnostics().size(), 3);
    for (auto diagnostic : SUT.get_diagnostics()) {
        ASSERT_EQ(diagnostic.level, fast::rf::Level::INFO);
        ASSERT_EQ(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
    }

    for (auto diagnostic : SUT.get_diagnostics()) {
        ASSERT_TRUE(SUT.update_diagnostic(diagnostic.diagnosticType, fast::rf::Level::NOERROR,
                                          fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "All Good"));
    }
    for (auto diagnostic : SUT.get_diagnostics()) {
        ASSERT_EQ(diagnostic.level, fast::rf::Level::NOERROR);
        ASSERT_EQ(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR);
    }
    ASSERT_FALSE(SUT.update_diagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::POSE, fast::rf::Level::DEBUG,
                                       fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR,
                                       "No problem,but this diagnostic isn't initialized."));
}
TEST(DiagnosticManager, GetDiagnosticsAtAboveThreshold) {
    DiagnosticManager SUT(1, 2, 3);
    std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
    diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
    diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::COMMUNICATIONS);
    diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::PLANNING);
    ASSERT_TRUE(SUT.initialize_diagnostics(diagnostic_types));
    ASSERT_TRUE(SUT.is_initialized());
    ASSERT_EQ(SUT.get_diagnostics().size(), 3);
    for (auto diagnostic : SUT.get_diagnostics()) {
        ASSERT_EQ(diagnostic.level, fast::rf::Level::INFO);
        ASSERT_EQ(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
    }
    ASSERT_EQ(SUT.get_diagnostics(fast::rf::Level::DEBUG).size(), 3);
    ASSERT_EQ(SUT.get_diagnostics(fast::rf::Level::INFO).size(), 3);
    ASSERT_EQ(SUT.get_diagnostics(fast::rf::Level::NOTICE).size(), 0);

    ASSERT_TRUE(SUT.update_diagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::ERROR,
                                      fast::rf::DiagnosticDefinition::DiagnosticMessage::NODATA,
                                      "Testing Error Condition"));
    ASSERT_EQ(SUT.get_diagnostics(fast::rf::Level::DEBUG).size(), 3);
    ASSERT_EQ(SUT.get_diagnostics(fast::rf::Level::INFO).size(), 3);
    ASSERT_EQ(SUT.get_diagnostics(fast::rf::Level::NOTICE).size(), 1);
    ASSERT_EQ(SUT.get_diagnostics(fast::rf::Level::WARN).size(), 1);
    ASSERT_EQ(SUT.get_diagnostics(fast::rf::Level::ERROR).size(), 1);
    ASSERT_EQ(SUT.get_diagnostics(fast::rf::Level::FATAL).size(), 0);

    ASSERT_TRUE(SUT.update_diagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE,
                                      fast::rf::Level::NOERROR,
                                      fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "All Ok"));
    ASSERT_TRUE(SUT.update_diagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::COMMUNICATIONS,
                                      fast::rf::Level::NOERROR,
                                      fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "All Ok"));
    ASSERT_TRUE(SUT.update_diagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::PLANNING,
                                      fast::rf::Level::NOERROR,
                                      fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "All Ok"));
    ASSERT_EQ(SUT.get_diagnostics(fast::rf::Level::NOERROR).size(), 3);
    ASSERT_EQ(SUT.get_diagnostics(fast::rf::Level::DEBUG).size(), 0);
}