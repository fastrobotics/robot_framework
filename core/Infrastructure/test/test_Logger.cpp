
#include <gtest/gtest.h>

#include <Infrastructure/Logger.hpp>
using namespace fast::rf;
class UserClass {
   public:
    UserClass() = default;
    virtual ~UserClass() = default;
    UserClass(Logger* logger_) { logger = logger_; }
    bool are_you_ok() {
        logger->log_warn("I'm Fine.");
        return true;
    }

   private:
    Logger* logger{nullptr};
};
TEST(Logger, BasicAssertions) {
    Logger* logger = new Logger(Level::DEBUG, "test_Logger");
    ASSERT_TRUE(logger != nullptr);
    ASSERT_TRUE(logger->is_logger_ok());
    logger->log_debug("Help!");
    logger->log_warn("What's Up?");
    UserClass SUT(logger);
    ASSERT_TRUE(SUT.are_you_ok());
    delete logger;
}