
#include <gtest/gtest.h>

#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <RobotFrameworkDefinitions.hpp>
using namespace fast::rf::core::infrastructure;
TEST(DiagnosticManager, BasicAssertions) {
    DiagnosticManager sut(1, 2, 3);
    std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
    diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
    ASSERT_TRUE(sut.initializeDiagnostics(diagnosticTypes));
    ASSERT_TRUE(sut.isInitialized());
    ASSERT_GT(sut.getDiagnostics().size(), 0);
    for (auto diagnostic : sut.getDiagnostics()) {
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
    DiagnosticManager sut(1, 2, 3);
    std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
    for (uint8_t i = 1; i < (uint8_t)fast::rf::DiagnosticDefinition::DiagnosticType::END_OF_LIST; ++i) {
        diagnosticTypes.push_back((fast::rf::DiagnosticDefinition::DiagnosticType)i);
    }

    ASSERT_TRUE(sut.initializeDiagnostics(diagnosticTypes));
    ASSERT_TRUE(sut.isInitialized());
    ASSERT_GT(sut.getDiagnostics().size(), 0);
    for (auto diagnostic : sut.getDiagnostics()) {
        ASSERT_EQ(diagnostic.systemID, 1);
        ASSERT_EQ(diagnostic.subsystemID, 2);
        ASSERT_EQ(diagnostic.processID, 3);
        ASSERT_NE(diagnostic.diagnosticType, fast::rf::DiagnosticDefinition::DiagnosticType::UNKNOWN);
        ASSERT_NE(diagnostic.diagnosticType, fast::rf::DiagnosticDefinition::DiagnosticType::END_OF_LIST);
        ASSERT_EQ(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
        ASSERT_EQ(diagnostic.level, fast::rf::Level::INFO);
        ASSERT_NE(diagnostic.description, "");
    }
    printf("%s\n", sut.pretty().c_str());

    for (uint8_t i = 1; i < (uint8_t)fast::rf::DiagnosticDefinition::DiagnosticMessage::END_OF_LIST; ++i) {
        ASSERT_TRUE(sut.updateDiagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE,
                                         fast::rf::Level::DEBUG, (fast::rf::DiagnosticDefinition::DiagnosticMessage)i,
                                         "Testing this..."));
        printf("%s\n", sut.pretty().c_str());
    }
}
TEST(DiagnosticManager, ImproperConstruction) {
    {
        DiagnosticManager sut(0, 1, 2);
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
        EXPECT_FALSE(sut.initializeDiagnostics(diagnosticTypes));
        EXPECT_FALSE(sut.isInitialized());
        EXPECT_EQ(sut.getDiagnostics().size(), 0);
    }
    {
        DiagnosticManager sut(1, 0, 2);
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
        EXPECT_FALSE(sut.initializeDiagnostics(diagnosticTypes));
        EXPECT_FALSE(sut.isInitialized());
        EXPECT_EQ(sut.getDiagnostics().size(), 0);
    }
    {
        DiagnosticManager sut(1, 2, 0);
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
        EXPECT_FALSE(sut.initializeDiagnostics(diagnosticTypes));
        EXPECT_FALSE(sut.isInitialized());
        EXPECT_EQ(sut.getDiagnostics().size(), 0);
    }
}
TEST(DiagnosticManager, Printing) {
    DiagnosticManager sut(1, 2, 3);
    std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
    diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
    diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::COMMUNICATIONS);
    diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::PLANNING);
    ASSERT_TRUE(sut.initializeDiagnostics(diagnosticTypes));
    ASSERT_TRUE(sut.isInitialized());
    ASSERT_EQ(sut.getDiagnostics().size(), 3);
    std::string str = sut.pretty();
    ASSERT_GT(str.size(), 0);
    printf("%s", str.c_str());
}
TEST(DiagnosticManager, UpdateDiagnostic) {
    DiagnosticManager sut(1, 2, 3);
    std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
    diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
    diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::COMMUNICATIONS);
    diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::PLANNING);
    ASSERT_TRUE(sut.initializeDiagnostics(diagnosticTypes));
    ASSERT_TRUE(sut.isInitialized());
    ASSERT_EQ(sut.getDiagnostics().size(), 3);
    for (auto diagnostic : sut.getDiagnostics()) {
        ASSERT_EQ(diagnostic.level, fast::rf::Level::INFO);
        ASSERT_EQ(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
    }

    for (auto diagnostic : sut.getDiagnostics()) {
        ASSERT_TRUE(sut.updateDiagnostic(diagnostic.diagnosticType, fast::rf::Level::NOERROR,
                                         fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "All Good"));
    }
    for (auto diagnostic : sut.getDiagnostics()) {
        ASSERT_EQ(diagnostic.level, fast::rf::Level::NOERROR);
        ASSERT_EQ(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR);
    }
    ASSERT_FALSE(sut.updateDiagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::POSE, fast::rf::Level::DEBUG,
                                      fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR,
                                      "No problem,but this diagnostic isn't initialized."));
}
TEST(DiagnosticManager, GetDiagnosticsAtAboveThreshold) {
    DiagnosticManager sut(1, 2, 3);
    std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
    diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
    diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::COMMUNICATIONS);
    diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::PLANNING);
    ASSERT_TRUE(sut.initializeDiagnostics(diagnosticTypes));
    ASSERT_TRUE(sut.isInitialized());
    ASSERT_EQ(sut.getDiagnostics().size(), 3);
    for (auto diagnostic : sut.getDiagnostics()) {
        ASSERT_EQ(diagnostic.level, fast::rf::Level::INFO);
        ASSERT_EQ(diagnostic.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::INITIALIZING);
    }
    ASSERT_EQ(sut.getDiagnostics(fast::rf::Level::DEBUG).size(), 3);
    ASSERT_EQ(sut.getDiagnostics(fast::rf::Level::INFO).size(), 3);
    ASSERT_EQ(sut.getDiagnostics(fast::rf::Level::NOTICE).size(), 0);

    ASSERT_TRUE(sut.updateDiagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::ERROR,
                                     fast::rf::DiagnosticDefinition::DiagnosticMessage::NODATA,
                                     "Testing Error Condition"));
    ASSERT_EQ(sut.getDiagnostics(fast::rf::Level::DEBUG).size(), 3);
    ASSERT_EQ(sut.getDiagnostics(fast::rf::Level::INFO).size(), 3);
    ASSERT_EQ(sut.getDiagnostics(fast::rf::Level::NOTICE).size(), 1);
    ASSERT_EQ(sut.getDiagnostics(fast::rf::Level::WARN).size(), 1);
    ASSERT_EQ(sut.getDiagnostics(fast::rf::Level::ERROR).size(), 1);
    ASSERT_EQ(sut.getDiagnostics(fast::rf::Level::FATAL).size(), 0);

    ASSERT_TRUE(sut.updateDiagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::NOERROR,
                                     fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "All Ok"));
    ASSERT_TRUE(sut.updateDiagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::COMMUNICATIONS,
                                     fast::rf::Level::NOERROR,
                                     fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "All Ok"));
    ASSERT_TRUE(sut.updateDiagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::PLANNING, fast::rf::Level::NOERROR,
                                     fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "All Ok"));
    ASSERT_EQ(sut.getDiagnostics(fast::rf::Level::NOERROR).size(), 3);
    ASSERT_EQ(sut.getDiagnostics(fast::rf::Level::DEBUG).size(), 0);
}