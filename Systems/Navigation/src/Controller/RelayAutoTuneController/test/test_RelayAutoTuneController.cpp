#include <gtest/gtest.h>

#include <Controller/RelayAutoTuneController/RelayAutoTuneController.hpp>
#include <cmath>

using namespace fast::rf::NavigationSystem::Controller;

TEST(RelayAutoTuneController, CalculatesZieglerNicholsGains) {
    RelayAutoTuneController controller;
    RelayAutoTuneControllerConfig config;
    config.set_parameters(5.0, -5.0, 2.0, 0.0, 1.0, 2);

    ASSERT_TRUE(controller.set_config(config));
    ASSERT_TRUE(controller.init());
    ASSERT_TRUE(controller.new_set_point(0.0, 0.0));
    ASSERT_TRUE(controller.start_tuning());
    RelayAutoTuneControllerOutput* output = controller.get_output();
    ASSERT_DOUBLE_EQ(output->command_value, 2.0);
    ASSERT_TRUE(output->is_new);

    ASSERT_TRUE(controller.new_sensor_input(1.0, 0.0));
    ASSERT_TRUE(controller.new_sensor_input(-1.0, 1.0));
    ASSERT_TRUE(controller.new_sensor_input(1.0, 2.0));
    ASSERT_TRUE(controller.new_sensor_input(-1.0, 3.0));
    ASSERT_TRUE(controller.new_sensor_input(1.0, 4.0));
    ASSERT_TRUE(controller.new_sensor_input(-1.0, 5.0));

    ASSERT_TRUE(controller.tuning_succeeded());
    output = controller.get_output();
    ASSERT_EQ(output->state, RelayAutoTuneState::COMPLETE);
    ASSERT_DOUBLE_EQ(output->response_amplitude, 1.0);
    ASSERT_DOUBLE_EQ(output->ultimate_period_sec, 2.0);

    const double ultimate_gain = 8.0 / M_PI;
    PIDControllerConfig tuned_config = controller.get_tuned_config();
    ASSERT_NEAR(tuned_config.get_K_P(), 0.6 * ultimate_gain, 1e-12);
    ASSERT_NEAR(tuned_config.get_K_I(), 0.6 * ultimate_gain, 1e-12);
    ASSERT_NEAR(tuned_config.get_K_D(), 0.15 * ultimate_gain, 1e-12);
}

TEST(RelayAutoTuneController, RejectsInvalidConfiguration) {
    RelayAutoTuneControllerConfig config;
    config.set_parameters(1.0, -1.0, 2.0, 0.0, 1.0, 1);
    ASSERT_FALSE(config.is_ok());
}

TEST(RelayAutoTuneController, EntersFailedStateWhenStartedWithoutConfiguration) {
    RelayAutoTuneController controller;
    ASSERT_TRUE(controller.init());
    ASSERT_FALSE(controller.start_tuning());
    ASSERT_EQ(controller.get_state(), RelayAutoTuneState::FAILED);

    RelayAutoTuneControllerOutput* output = controller.get_output();
    ASSERT_EQ(output->state, RelayAutoTuneState::FAILED);
    ASSERT_TRUE(output->is_new);
}

TEST(RelayAutoTuneController, DoesNotCompleteWithoutMeasurablePeriod) {
    RelayAutoTuneController controller;
    RelayAutoTuneControllerConfig config;
    config.set_parameters(5.0, -5.0, 2.0, 0.0, 1.0, 2);

    ASSERT_TRUE(controller.set_config(config));
    ASSERT_TRUE(controller.init());
    ASSERT_TRUE(controller.new_set_point(0.0, 0.0));
    ASSERT_TRUE(controller.start_tuning());

    ASSERT_TRUE(controller.new_sensor_input(1.0, 0.0));
    ASSERT_TRUE(controller.new_sensor_input(-1.0, 0.0));
    ASSERT_TRUE(controller.new_sensor_input(1.0, 0.0));
    ASSERT_EQ(controller.get_state(), RelayAutoTuneState::TUNING);

    RelayAutoTuneControllerOutput* output = controller.get_output();
    ASSERT_EQ(output->state, RelayAutoTuneState::TUNING);
    ASSERT_TRUE(output->is_new);
    ASSERT_DOUBLE_EQ(output->ultimate_period_sec, 0.0);
}

TEST(RelayAutoTuneController, IgnoresCrossingsDuringMinimumSwitchTime) {
    RelayAutoTuneController controller;
    RelayAutoTuneControllerConfig config;
    config.set_parameters(5.0, -5.0, 2.0, 0.0, 1.0, 2, 0.1);

    ASSERT_TRUE(controller.set_config(config));
    ASSERT_TRUE(controller.init());
    ASSERT_TRUE(controller.new_set_point(0.0, 0.0));
    ASSERT_TRUE(controller.start_tuning());

    ASSERT_TRUE(controller.new_sensor_input(1.0, 0.0));
    ASSERT_TRUE(controller.new_sensor_input(-1.0, 0.01));
    ASSERT_TRUE(controller.new_sensor_input(1.0, 0.02));
    ASSERT_EQ(controller.get_state(), RelayAutoTuneState::TUNING);
}

TEST(RelayAutoTuneController, HoldsRelayCommandBeforeAllowingSwitch) {
    RelayAutoTuneController controller;
    RelayAutoTuneControllerConfig config;
    config.set_parameters(5.0, -5.0, 2.0, 0.0, 1.0, 2, 0.1, 1.0e-3, 0.25);

    ASSERT_TRUE(controller.set_config(config));
    ASSERT_TRUE(controller.init());
    ASSERT_TRUE(controller.new_set_point(0.0, 0.0));
    ASSERT_TRUE(controller.start_tuning());

    ASSERT_TRUE(controller.new_sensor_input(1.0, 0.0));
    ASSERT_TRUE(controller.new_sensor_input(-1.0, 0.1));
    RelayAutoTuneControllerOutput* output = controller.get_output();
    ASSERT_DOUBLE_EQ(output->command_value, 2.0);

    ASSERT_TRUE(controller.new_sensor_input(1.0, 0.2));
    ASSERT_EQ(controller.get_state(), RelayAutoTuneState::TUNING);
    output = controller.get_output();
    ASSERT_DOUBLE_EQ(output->command_value, 2.0);
}
