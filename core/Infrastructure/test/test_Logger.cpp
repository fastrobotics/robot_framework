
#include <gtest/gtest.h>

#include <Infrastructure/Logger.hpp>
using namespace fast::rf;
class UserClass {
   public:
    UserClass() = default;
    virtual ~UserClass() = default;
    bool are_you_ok() {
        auto status = Logger::log_warn("I'm Ok");
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
    ASSERT_EQ(Logger::log_debug("Help"), Logger::LoggerStatus::LOG_SUPPRESSED);
    ASSERT_EQ(Logger::log_info("I'm Ok"), Logger::LoggerStatus::LOG_WRITTEN);
    UserClass SUT;
    ASSERT_TRUE(SUT.are_you_ok());
}
TEST(Logger, ExceptionalCases) {
    ASSERT_TRUE(Logger::init(Level::DEBUG, "/Test-Logger2"));
    ASSERT_EQ(Logger::log_debug("Help"), Logger::LoggerStatus::LOG_WRITTEN);
    Logger::log_warn("What's up?");
    UserClass SUT;
    ASSERT_TRUE(SUT.are_you_ok());
    ASSERT_FALSE(Logger::init(Level::DEBUG, "/Test-Logger2"));  // Already Initialized
}
TEST(Logger, NegativeAssertions) {
    ASSERT_FALSE(Logger::init(Level::UNKNOWN, "Test-Logger3"));
    ASSERT_EQ(Logger::log_debug("An Error Message that won't get printed"), Logger::LoggerStatus::FAILED_TO_OPEN);
}
TEST(Logger, LoggerLevelChecks) {
    ASSERT_TRUE(Logger::init(Level::DEBUG, "Test-Logger"));
    ASSERT_EQ(Logger::log_debug("A Test Debug Message"), Logger::LoggerStatus::LOG_WRITTEN);
    ASSERT_EQ(Logger::log_info("A Test Info Message"), Logger::LoggerStatus::LOG_WRITTEN);
    ASSERT_EQ(Logger::log_notice("A Test Notice Message"), Logger::LoggerStatus::LOG_WRITTEN);
    ASSERT_EQ(Logger::log_warn("A Test Warn Message"), Logger::LoggerStatus::LOG_WRITTEN);
    ASSERT_EQ(Logger::log_error("A Test Error Message"), Logger::LoggerStatus::LOG_WRITTEN);
    ASSERT_EQ(Logger::log_fatal("A Test Fatal Message"), Logger::LoggerStatus::LOG_WRITTEN);
}
TEST(Logger, LongFile) {
    ASSERT_TRUE(Logger::init(Level::DEBUG, "Test-Logger-LongFile"));
    UserClass SUT;
    uint16_t line_counter = 0;
    while (line_counter < (Logger::MAXLINE_COUNT * 2)) {
        line_counter++;
        ASSERT_TRUE(SUT.are_you_ok());
    }
}
TEST(Logger, LazyInitializationWithoutExplicitInit) {
    Logger::shutdown();
    ASSERT_EQ(Logger::log_debug("Lazy initialization should work without an explicit init"),
              Logger::LoggerStatus::LOG_WRITTEN);
    Logger::shutdown();
}