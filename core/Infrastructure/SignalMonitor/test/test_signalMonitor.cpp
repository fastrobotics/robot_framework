
#include <gtest/gtest.h>

#include <Infrastructure/Logger.hpp>
#include <Infrastructure/SignalMonitor/SignalMonitor.hpp>
using namespace fast::rf::core::infrastructure;
TEST(SignalMonitor, BasicTests) { SignalMonitor SUT("test_signal", "test_type", 1.0, 100.0); }
TEST(SignalMonitor, HappyFlow) {
    double expectedRate = 10.0;
    double rateTolerancePerc = 90.0;
    SignalMonitor SUT("test_signal", "test_type", expectedRate, rateTolerancePerc);
    ASSERT_EQ(SUT.getStatus().level, fast::rf::Level::UNKNOWN);
    double runTime = 10.0;
    double dt = 1.0 / expectedRate;
    double curTime = 0.0;
    uint32_t counter = 0;
    while (curTime <= runTime) {
        ASSERT_TRUE(SUT.newData(curTime));
        ASSERT_TRUE(SUT.update(curTime));
        fast::rf::Logger::logInfo(SUT.pretty());
        if (counter >= SignalMonitor::INITIAL_SAMPLES_TO_ACCUMULATE) {
            ASSERT_NE(SUT.getStatus().level, fast::rf::Level::UNKNOWN);
            ASSERT_LT(SUT.getStatus().level, fast::rf::Level::WARN);
        }
        curTime += dt;
        counter += 1;
    }
}

TEST(SignalMonitor, LowRateData) {
    double expectedRate = 10.0;
    double rateTolerancePerc = 90.0;
    SignalMonitor SUT("test_signal", "test_type", expectedRate, rateTolerancePerc);
    ASSERT_EQ(SUT.getStatus().level, fast::rf::Level::UNKNOWN);
    double runTime = 10.0;
    double dt = 1.0 / expectedRate;
    double curTime = 0.0;
    uint32_t counter = 0;
    while (curTime <= runTime) {
        // Skip every 5th sample
        if (counter % 5 == 0) {
        } else {
            ASSERT_TRUE(SUT.newData(curTime));
        }

        ASSERT_TRUE(SUT.update(curTime));
        fast::rf::Logger::logInfo(SUT.pretty());
        curTime += dt;
        counter += 1;
    }
    ASSERT_NE(SUT.getStatus().level, fast::rf::Level::UNKNOWN);
    ASSERT_GT(SUT.getStatus().level, fast::rf::Level::INFO);
}