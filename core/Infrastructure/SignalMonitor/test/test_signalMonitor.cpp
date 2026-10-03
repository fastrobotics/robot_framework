
#include <gtest/gtest.h>

#include <Infrastructure/Logger.hpp>
#include <Infrastructure/SignalMonitor/SignalMonitor.hpp>
using namespace fast::rf::core::infrastructure;
TEST(SignalMonitor, BasicTests) { SignalMonitor SUT("test_signal", "test_type", 1.0); }
TEST(SignalMonitor, HappyFlow) {
    double expectedRate = 10.0;
    SignalMonitor SUT("test_signal", "test_type", expectedRate);
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
            // ASSERT_EQ(SUT.getLevel(), fast::rf::Level::INFO);
        }
        curTime += dt;
        counter += 1;
    }
}