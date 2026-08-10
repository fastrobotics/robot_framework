#include <gtest/gtest.h>

#include <Controller/PIDController/PIDController.hpp>
using namespace fast::rf::NavigationSystem::Controller;

TEST(PIDController, BasicAssertions) {
    PIDController SUT;
    IControllerConfig* config = new PIDControllerConfig;
    ASSERT_TRUE(SUT.init(config));
    ASSERT_FLOAT_EQ(SUT.get_sensor_delta_time_sec(), -1.0);
    fast::rf::Logger::log_debug(SUT.pretty());
    double current_time_sec = 0.0;
    ASSERT_TRUE(SUT.new_set_point(0.0, current_time_sec));
    ASSERT_TRUE(SUT.new_sensor_input(0.0, current_time_sec));
    ASSERT_FLOAT_EQ(SUT.get_sensor_delta_time_sec(), -1.0);
    current_time_sec += 1.0;
    ASSERT_TRUE(SUT.update(current_time_sec));

    ASSERT_TRUE(SUT.new_sensor_input(0.0, current_time_sec));
    ASSERT_GT(SUT.get_sensor_delta_time_sec(), 0.0);
    auto output = SUT.get_output();
    ASSERT_NE(output, nullptr);
    ASSERT_TRUE(output->is_new);
    output = SUT.get_output();
    ASSERT_FALSE(output->is_new);
    fast::rf::Logger::log_debug(SUT.pretty());
}