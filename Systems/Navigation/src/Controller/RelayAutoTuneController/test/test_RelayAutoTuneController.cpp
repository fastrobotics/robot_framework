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

    ASSERT_TRUE(controller.new_sensor_input(1.0, 0.0));
    ASSERT_TRUE(controller.new_sensor_input(-1.0, 1.0));
    ASSERT_TRUE(controller.new_sensor_input(1.0, 2.0));
    ASSERT_TRUE(controller.new_sensor_input(-1.0, 3.0));
    ASSERT_TRUE(controller.new_sensor_input(1.0, 4.0));
    ASSERT_TRUE(controller.new_sensor_input(-1.0, 5.0));

    ASSERT_TRUE(controller.tuning_succeeded());
    RelayAutoTuneControllerOutput* output = controller.get_output();
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
