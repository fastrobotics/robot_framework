
#include <gtest/gtest.h>

#include <DiagnosticMsg.hpp>
#include <Infrastructure/Logger.hpp>
using namespace fast::rf;
class UserClass {
   public:
    UserClass() = default;
    virtual ~UserClass() = default;
    bool areYouOk() {
        auto status = Logger::logWarn("I'm Ok");
        if (status == Logger::LoggerStatus::LOG_WRITTEN) {
            return true;
        } else {
            return false;
        }
    }

   private:
};

TEST(Logger, BasicAssertions) {
    ASSERT_TRUE(Logger::init(Level::INFO, "Test-Logger"));
    ASSERT_EQ(Logger::logDebug("Help"), Logger::LoggerStatus::LOG_SUPPRESSED);
    ASSERT_EQ(Logger::logInfo("I'm Ok"), Logger::LoggerStatus::LOG_WRITTEN);
    UserClass sut;
    ASSERT_TRUE(sut.areYouOk());
}
TEST(Logger, ExceptionalCases) {
    ASSERT_TRUE(Logger::init(Level::DEBUG, "/Test-Logger2"));
    ASSERT_EQ(Logger::logDebug("Help"), Logger::LoggerStatus::LOG_WRITTEN);
    Logger::logWarn("What's up?");
    UserClass sut;
    ASSERT_TRUE(sut.areYouOk());
    ASSERT_FALSE(Logger::init(Level::DEBUG, "/Test-Logger2"));  // Already Initialized
}
TEST(Logger, NegativeAssertions) {
    ASSERT_FALSE(Logger::init(Level::UNKNOWN, "Test-Logger3"));
    ASSERT_EQ(Logger::logDebug("An Error Message that won't get printed"), Logger::LoggerStatus::FAILED_TO_OPEN);
}
TEST(Logger, LoggerLevelChecks) {
    ASSERT_TRUE(Logger::init(Level::DEBUG, "Test-Logger"));
    ASSERT_EQ(Logger::logDebug("A Test Debug Message"), Logger::LoggerStatus::LOG_WRITTEN);
    ASSERT_EQ(Logger::logInfo("A Test Info Message"), Logger::LoggerStatus::LOG_WRITTEN);
    ASSERT_EQ(Logger::logNotice("A Test Notice Message"), Logger::LoggerStatus::LOG_WRITTEN);
    ASSERT_EQ(Logger::logWarn("A Test Warn Message"), Logger::LoggerStatus::LOG_WRITTEN);
    ASSERT_EQ(Logger::logError("A Test Error Message"), Logger::LoggerStatus::LOG_WRITTEN);
    ASSERT_EQ(Logger::logFatal("A Test Fatal Message"), Logger::LoggerStatus::LOG_WRITTEN);
}
TEST(Logger, LongFile) {
    ASSERT_TRUE(Logger::init(Level::DEBUG, "Test-Logger-LongFile"));
    UserClass sut;
    uint16_t lineCounter = 0;
    while (lineCounter < (Logger::MAXLINE_COUNT * 2)) {
        lineCounter++;
        ASSERT_TRUE(sut.areYouOk());
    }
}
using namespace fast::rf::messages::InfrastructureMsgs;
TEST(Logger, LogDiagnostics) {
    DiagnosticMsg diagnostic(1, 2, 3, fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
    diagnostic.description = "Some Diagnostic Message";
    for (uint8_t i = 0; i < (uint8_t)fast::rf::Level::END_OF_LIST; ++i) {
        diagnostic.level = (fast::rf::Level)i;
        ASSERT_EQ(Logger::logDiagnostic(diagnostic), Logger::LoggerStatus::LOG_WRITTEN);
    }
}
TEST(Logger, LazyInitializationWithoutExplicitInit) {
    Logger::shutdown();
    ASSERT_EQ(Logger::logDebug("Lazy initialization should work without an explicit init"),
              Logger::LoggerStatus::LOG_WRITTEN);
    Logger::shutdown();
}