#include <gtest/gtest.h>

#include <ControllerTuner/PIDAutoTuner/PIDAutoTuner.hpp>

using namespace fast::rf::NavigationSystem::ControllerTuner;
using namespace fast::rf::NavigationSystem::Controller;

TEST(PIDAutoTuner, HappyFlow) {
    PIDAutoTuner tuner;
    PIDAutoTunerConfig config;
    config.set_parameters(10.0, -10.0, 0.0, 0.0, 0.0, 1.0);
    config.set_tuning_parameters(2.0, 1.0, 1.0, 3.0, 0.5);

    ASSERT_TRUE(tuner.set_config(config));
    ASSERT_TRUE(tuner.init());
    ASSERT_TRUE(tuner.start_tuning());
    ASSERT_TRUE(tuner.new_sensor_input(10.0, 0.0));

    PIDAutoTunerOutput* output = tuner.get_output();
    ASSERT_TRUE(output->is_new);
    ASSERT_EQ(output->state, AutoTunerState::TUNING);
    ASSERT_EQ(output->algorithm_state, PIDAutoTunerAlgorithmState::APPLY_STEP);
    ASSERT_DOUBLE_EQ(output->set_point, 11.0);

    ASSERT_TRUE(tuner.update(0.0));
    output = tuner.get_output();
    ASSERT_TRUE(output->is_new);
    ASSERT_EQ(output->algorithm_state, PIDAutoTunerAlgorithmState::MEASURE_RESPONSE);
    ASSERT_DOUBLE_EQ(output->command_value, 2.0);

    ASSERT_TRUE(tuner.new_sensor_input(11.0, 1.0));
    ASSERT_TRUE(tuner.update(1.0));
    output = tuner.get_output();
    ASSERT_TRUE(output->is_new);
    ASSERT_EQ(output->state, AutoTunerState::TUNING);
    ASSERT_EQ(output->algorithm_state, PIDAutoTunerAlgorithmState::EVALUATE_PID);
    ASSERT_GT(output->K_P, 0.0);
    ASSERT_GT(output->K_I, 0.0);
    ASSERT_GT(output->K_D, 0.0);

    ASSERT_TRUE(tuner.update(2.0));
    ASSERT_TRUE(tuner.update(3.0));
    output = tuner.get_output();
    ASSERT_EQ(output->state, AutoTunerState::COMPLETE);
    ASSERT_EQ(output->algorithm_state, PIDAutoTunerAlgorithmState::COMPLETE);
}

TEST(PIDAutoTuner, RequiresBothParameterGroups) {
    PIDAutoTuner tuner;
    PIDAutoTunerConfig config;
    config.set_parameters(10.0, -10.0, 0.0, 0.0, 0.0, 1.0);

    ASSERT_FALSE(tuner.set_config(config));
    ASSERT_TRUE(tuner.init());
    ASSERT_FALSE(tuner.start_tuning());
    ASSERT_EQ(tuner.get_state(), AutoTunerState::FAILED);
}

TEST(PIDAutoTuner, ReportsInvalidConfigurationFailureDetails) {
    PIDAutoTuner tuner;
    ASSERT_TRUE(tuner.init());
    ASSERT_FALSE(tuner.start_tuning());

    PIDAutoTunerOutput* output = tuner.get_output();
    ASSERT_EQ(output->failure_reason, PIDAutoTunerFailureReason::INVALID_CONFIGURATION);
    ASSERT_EQ(output->failure_reason_string, "INVALID_CONFIGURATION");
    ASSERT_EQ(output->failure_attribute, "PIDAutoTunerConfig");
    ASSERT_FALSE(output->failure_remediation.empty());
}

TEST(PIDAutoTuner, SelectsSupportedStepResponseAlgorithm) {
    PIDAutoTunerConfig config;
    config.set_parameters(10.0, -10.0, 0.0, 0.0, 0.0, 1.0);
    config.set_tuning_parameters(2.0, 1.0, 1.0, 3.0, 0.5);
    config.set_algorithm(PIDAutoTuningAlgorithm::STEP_RESPONSE);

    ASSERT_EQ(config.get_algorithm(), PIDAutoTuningAlgorithm::STEP_RESPONSE);
    ASSERT_TRUE(config.is_ok());
}

TEST(PIDAutoTuner, CalculatesIMCLambdaGains) {
    PIDAutoTuner tuner;
    PIDAutoTunerConfig config;
    config.set_parameters(10.0, -10.0, 0.0, 0.0, 0.0, 1.0);
    config.set_tuning_parameters(2.0, 1.0, 1.0, 3.0, 0.5);
    config.set_algorithm(PIDAutoTuningAlgorithm::IMC_LAMBDA);
    config.set_imc_parameters(0.2, 2.0);

    ASSERT_TRUE(tuner.set_config(config));
    ASSERT_TRUE(tuner.init());
    ASSERT_TRUE(tuner.start_tuning());
    ASSERT_TRUE(tuner.new_sensor_input(10.0, 0.0));
    ASSERT_TRUE(tuner.update(0.0));
    ASSERT_TRUE(tuner.new_sensor_input(11.0, 1.0));
    ASSERT_TRUE(tuner.update(1.0));

    PIDAutoTunerOutput* output = tuner.get_output();
    ASSERT_EQ(output->algorithm_state, PIDAutoTunerAlgorithmState::EVALUATE_PID);
    ASSERT_NEAR(output->K_P, 1.1 / 1.05, 1e-12);
    ASSERT_NEAR(output->K_I, (1.1 / 1.05) / 1.1, 1e-12);
    ASSERT_NEAR(output->K_D, (1.1 / 1.05) * (0.2 / 2.2), 1e-12);
}

TEST(PIDAutoTuner, FailsWhenResponseTimesOut) {
    PIDAutoTuner tuner;
    PIDAutoTunerConfig config;
    config.set_parameters(10.0, -10.0, 0.0, 0.0, 0.0, 1.0);
    config.set_tuning_parameters(2.0, 1.0, 1.0, 2.0, 0.5);

    ASSERT_TRUE(tuner.set_config(config));
    ASSERT_TRUE(tuner.init());
    ASSERT_TRUE(tuner.start_tuning());
    ASSERT_TRUE(tuner.new_sensor_input(10.0, 0.0));
    ASSERT_TRUE(tuner.update(0.0));
    ASSERT_FALSE(tuner.update(2.0));
    ASSERT_EQ(tuner.get_state(), AutoTunerState::FAILED);
    ASSERT_EQ(tuner.get_algorithm_state(), PIDAutoTunerAlgorithmState::FAILED);
    PIDAutoTunerOutput* output = tuner.get_output();
    ASSERT_EQ(output->failure_reason, PIDAutoTunerFailureReason::RESPONSE_TIMEOUT);
    ASSERT_EQ(output->failure_reason_string, "RESPONSE_TIMEOUT");
    ASSERT_EQ(output->failure_attribute, "elapsed_time_sec");
    ASSERT_FALSE(output->failure_remediation.empty());
}

TEST(PIDAutoTuner, IteratesGainsWhenTrackingErrorIsTooLarge) {
    PIDAutoTuner tuner;
    PIDAutoTunerConfig config;
    config.set_parameters(10.0, -10.0, 0.0, 0.0, 0.0, 1.0);
    config.set_tuning_parameters(2.0, 1.0, 1.0, 5.0, 0.5, 0.05, 1.0, 2);

    ASSERT_TRUE(tuner.set_config(config));
    ASSERT_TRUE(tuner.init());
    ASSERT_TRUE(tuner.start_tuning());
    ASSERT_TRUE(tuner.new_sensor_input(10.0, 0.0));
    ASSERT_TRUE(tuner.update(0.0));
    ASSERT_TRUE(tuner.new_sensor_input(11.0, 1.0));
    ASSERT_TRUE(tuner.update(1.0));

    PIDAutoTunerOutput* output = tuner.get_output();
    const double initial_K_P = output->K_P;
    ASSERT_EQ(output->algorithm_state, PIDAutoTunerAlgorithmState::EVALUATE_PID);

    ASSERT_TRUE(tuner.new_sensor_input(10.0, 2.0));
    ASSERT_TRUE(tuner.update(2.0));
    ASSERT_TRUE(tuner.new_sensor_input(10.0, 3.0));
    ASSERT_TRUE(tuner.update(3.0));
    output = tuner.get_output();
    ASSERT_EQ(output->state, AutoTunerState::TUNING);
    ASSERT_EQ(output->algorithm_state, PIDAutoTunerAlgorithmState::EVALUATE_PID);
    ASSERT_DOUBLE_EQ(output->K_P, initial_K_P * 1.5);

    ASSERT_TRUE(tuner.new_sensor_input(10.0, 4.0));
    ASSERT_TRUE(tuner.update(4.0));
    ASSERT_TRUE(tuner.new_sensor_input(10.0, 5.0));
    ASSERT_FALSE(tuner.update(5.0));
    ASSERT_EQ(tuner.get_state(), AutoTunerState::FAILED);
    output = tuner.get_output();
    ASSERT_EQ(output->failure_reason, PIDAutoTunerFailureReason::TUNING_ITERATION_LIMIT);
    ASSERT_EQ(output->failure_attribute, "maximum_tracking_error");
    ASSERT_FALSE(output->failure_remediation.empty());
}