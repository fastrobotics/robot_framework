
#include <gtest/gtest.h>

#include <Infrastructure/SingletonLogger.hpp>
using namespace fast::rf;
class UserClass {
   public:
    UserClass() = default;
    virtual ~UserClass() = default;
    bool are_you_ok() {
        SingletonLogger::log_warn("I'm Ok");
        return true;
    }

   private:
};

TEST(SingletonLogger, BasicAssertions) {
    ASSERT_TRUE(SingletonLogger::init(Level::DEBUG, "Test-SingletonLogger"));
    ASSERT_EQ(SingletonLogger::log_debug("Help"), SingletonLogger::LoggerStatus::LOG_WRITTEN);
    SingletonLogger::log_warn("What's up?");
    UserClass SUT;
    ASSERT_TRUE(SUT.are_you_ok());
}
TEST(SingletonLogger, NegativeAssertions) {
    ASSERT_FALSE(SingletonLogger::init(Level::UNKNOWN, "Test-SingletonLogger2"));
    ASSERT_EQ(SingletonLogger::log_debug("An Error Message that won't get printed"),
              SingletonLogger::LoggerStatus::FAILED_TO_OPEN);
}
TEST(SingletonLogger, LoggerLevelChecks) {
    ASSERT_TRUE(SingletonLogger::init(Level::DEBUG, "Test-SingletonLogger3"));
    ASSERT_EQ(SingletonLogger::log_debug("A Test Debug Message"), SingletonLogger::LoggerStatus::LOG_WRITTEN);
    ASSERT_EQ(SingletonLogger::log_info("A Test Info Message"), SingletonLogger::LoggerStatus::LOG_WRITTEN);
    ASSERT_EQ(SingletonLogger::log_notice("A Test Notice Message"), SingletonLogger::LoggerStatus::LOG_WRITTEN);
    ASSERT_EQ(SingletonLogger::log_warn("A Test Warn Message"), SingletonLogger::LoggerStatus::LOG_WRITTEN);
    ASSERT_EQ(SingletonLogger::log_error("A Test Error Message"), SingletonLogger::LoggerStatus::LOG_WRITTEN);
    ASSERT_EQ(SingletonLogger::log_fatal("A Test Fatal Message"), SingletonLogger::LoggerStatus::LOG_WRITTEN);
}