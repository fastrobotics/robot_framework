#include <gtest/gtest.h>

#include <Controller/RelayAutoTuneController/MockRelayAutoTuneController.hpp>

using namespace fast::rf::NavigationSystem::Controller;

TEST(MockRelayAutoTuneController, DrivesSetPointAndGains) {
    MockRelayAutoTuneController controller;
    RelayAutoTuneControllerConfig config;
    config.set_parameters(5.0, -5.0, 1.0, 0.0, 1.0, 4);

    ASSERT_TRUE(controller.set_config(config));
    ASSERT_TRUE(controller.init());
    controller.set_mock_gains(1.0, 0.2, 0.05);
    controller.set_mock_gain_step(0.5, 0.1, 0.02);
    controller.set_mock_set_point(10.0, 1.0);
    controller.set_mock_limits(9.0, 11.0, 0.5, 1.5, 0.1, 0.3, 0.03, 0.07);
    ASSERT_TRUE(controller.start_tuning());

    ASSERT_TRUE(controller.update(1.0));
    RelayAutoTuneControllerOutput* output = controller.get_output();
    ASSERT_DOUBLE_EQ(output->set_point, 11.0);
    ASSERT_DOUBLE_EQ(output->K_P, 1.5);
    ASSERT_DOUBLE_EQ(output->K_I, 0.3);
    ASSERT_DOUBLE_EQ(output->K_D, 0.07);
    ASSERT_EQ(output->state, RelayAutoTuneState::TUNING);

    ASSERT_TRUE(controller.update(2.0));
    output = controller.get_output();
    ASSERT_DOUBLE_EQ(output->set_point, 10.0);
    ASSERT_DOUBLE_EQ(output->K_P, 1.0);
    ASSERT_DOUBLE_EQ(output->K_I, 0.2);
    ASSERT_DOUBLE_EQ(output->K_D, 0.05);
}