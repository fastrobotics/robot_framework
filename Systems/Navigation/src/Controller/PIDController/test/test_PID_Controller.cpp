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
TEST(PIDController, SimpleCompute) {
    PIDController SUT;
    IControllerConfig* config = new PIDControllerConfig;
    auto* config_ = dynamic_cast<PIDControllerConfig*>(config);
    ASSERT_FALSE(config_ == nullptr);
    config_->set_parameters(2.0, 0.0, 0.0, 2.0);
    ASSERT_TRUE(SUT.init(config));
    double current_time_sec = 0.0;
    ASSERT_TRUE(SUT.new_set_point(1.0, current_time_sec));
    ASSERT_TRUE(SUT.new_sensor_input(0.2, current_time_sec));
    fast::rf::Logger::log_debug(SUT.pretty());
    auto output = SUT.get_output();
    ASSERT_TRUE(output->is_new);
    ASSERT_FLOAT_EQ(output->P_term, 1.2);
    ASSERT_FLOAT_EQ(output->I_term, 0.0);
    ASSERT_FLOAT_EQ(output->D_term, 0.0);
    ASSERT_FLOAT_EQ(output->setpoint_sensor_error, 0.6);
    ASSERT_FLOAT_EQ(output->command_value, 1.2);
}