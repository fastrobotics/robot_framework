#pragma once

#include <Controller/BaseController.hpp>
#include <Controller/PIDController/PIDController.hpp>
#include <cstddef>

namespace fast::rf::NavigationSystem::ControllerTuner {
    enum class AutoTunerState { IDLE, TUNING, COMPLETE, FAILED };
    enum class PIDAutoTunerFailureReason {
        NONE,
        INVALID_CONFIGURATION,
        RESPONSE_TIMEOUT,
        INSUFFICIENT_RESPONSE,
        TRACKING_ERROR_EXCEEDED,
        TUNING_ITERATION_LIMIT,
        UNSUPPORTED_ALGORITHM
    };
    enum class PIDAutoTuningAlgorithm {
        STEP_RESPONSE,
        IMC_LAMBDA,
        // RELAY_FEEDBACK,
        // ZIEGLER_NICHOLS_STEP_RESPONSE,
        // ZIEGLER_NICHOLS_ULTIMATE_GAIN,
        // COHEN_COON
    };
    enum class PIDAutoTunerAlgorithmState {
        IDLE,
        CAPTURE_BASELINE,
        APPLY_STEP,
        MEASURE_RESPONSE,
        EVALUATE_PID,
        COMPLETE,
        FAILED
    };

    class PIDAutoTunerConfig : public Controller::IControllerConfig {
       public:
        ~PIDAutoTunerConfig() override {}

        void set_parameters(double max_output, double min_output, double P, double I, double D,
                            double sensor_scale_factor) {
            max_output_ = max_output;
            min_output_ = min_output;
            K_P_ = P;
            K_I_ = I;
            K_D_ = D;
            sensor_scale_ = sensor_scale_factor;
            parameters_set_ = true;
        }

        void set_tuning_parameters(double output_step, double set_point_step, double settle_time_sec,
                                   double response_timeout_sec, double minimum_response,
                                   double acceptable_error_threshold = 0.05, double evaluation_time_sec = 1.0,
                                   std::size_t max_tuning_iterations = 3) {
            output_step_ = output_step;
            set_point_step_ = set_point_step;
            settle_time_sec_ = settle_time_sec;
            response_timeout_sec_ = response_timeout_sec;
            minimum_response_ = minimum_response;
            acceptable_error_threshold_ = acceptable_error_threshold;
            evaluation_time_sec_ = evaluation_time_sec;
            max_tuning_iterations_ = max_tuning_iterations;
            tuning_parameters_set_ = true;
        }

        void set_algorithm(PIDAutoTuningAlgorithm algorithm) { algorithm_ = algorithm; }
        void set_imc_parameters(double dead_time_sec, double lambda_sec) {
            dead_time_sec_ = dead_time_sec;
            lambda_sec_ = lambda_sec;
        }

        bool is_ok() override;
        std::string pretty() override;
        double get_K_P() const { return K_P_; }
        double get_K_I() const { return K_I_; }
        double get_K_D() const { return K_D_; }
        double get_sensor_scale() const { return sensor_scale_; }
        double get_output_step() const { return output_step_; }
        double get_set_point_step() const { return set_point_step_; }
        double get_settle_time_sec() const { return settle_time_sec_; }
        double get_response_timeout_sec() const { return response_timeout_sec_; }
        double get_minimum_response() const { return minimum_response_; }
        double get_acceptable_error_threshold() const { return acceptable_error_threshold_; }
        double get_evaluation_time_sec() const { return evaluation_time_sec_; }
        std::size_t get_max_tuning_iterations() const { return max_tuning_iterations_; }
        PIDAutoTuningAlgorithm get_algorithm() const { return algorithm_; }
        double get_dead_time_sec() const { return dead_time_sec_; }
        double get_lambda_sec() const { return lambda_sec_; }

       private:
        double K_P_{0.0};
        double K_I_{0.0};
        double K_D_{0.0};
        double sensor_scale_{1.0};
        double output_step_{0.0};
        double set_point_step_{0.0};
        double settle_time_sec_{0.0};
        double response_timeout_sec_{0.0};
        double minimum_response_{0.0};
        double acceptable_error_threshold_{0.05};
        double evaluation_time_sec_{1.0};
        std::size_t max_tuning_iterations_{3};
        PIDAutoTuningAlgorithm algorithm_{PIDAutoTuningAlgorithm::STEP_RESPONSE};
        double dead_time_sec_{0.0};
        double lambda_sec_{0.0};
        bool parameters_set_{false};
        bool tuning_parameters_set_{false};
    };

    class PIDAutoTunerOutput : public Controller::IControllerOutput {
       public:
        ~PIDAutoTunerOutput() override {}
        AutoTunerState state{AutoTunerState::IDLE};
        PIDAutoTunerFailureReason failure_reason{PIDAutoTunerFailureReason::NONE};
        std::string failure_reason_string;
        std::string failure_attribute;
        std::string failure_remediation;
        PIDAutoTuningAlgorithm algorithm{PIDAutoTuningAlgorithm::STEP_RESPONSE};
        PIDAutoTunerAlgorithmState algorithm_state{PIDAutoTunerAlgorithmState::IDLE};
        double set_point{0.0};
        double sensor_input{0.0};
        double K_P{0.0};
        double K_I{0.0};
        double K_D{0.0};
        double response{0.0};
        double tracking_error{0.0};
        double maximum_tracking_error{0.0};
        double elapsed_time_sec{0.0};
    };

    class PIDAutoTuner : public Controller::BaseController {
       public:
        Controller::ControllerType get_controller_type() override { return Controller::ControllerType::PID_AUTO_TUNER; }
        bool init() override;
        bool set_config(PIDAutoTunerConfig config);
        bool new_set_point(double set_point, double time_stamp_sec) override;
        bool new_sensor_input(double sensor_input, double time_stamp_sec) override;
        bool update(double current_time_sec) override;
        PIDAutoTunerOutput* get_output() override;
        std::string pretty() override;
        bool clear() override;

        bool start_tuning();
        bool is_tuning_complete() const { return state_ == AutoTunerState::COMPLETE; }
        bool tuning_succeeded() const { return is_tuning_complete(); }
        Controller::PIDControllerConfig get_tuned_config() const { return tuned_config_; }
        AutoTunerState get_state() const { return state_; }
        PIDAutoTunerAlgorithmState get_algorithm_state() const { return algorithm_state_; }

       private:
        bool run_tuning_step(double current_time_sec);
        bool run_step_response_tuning_step(double current_time_sec);
        void fail_tuning(PIDAutoTunerFailureReason reason, const std::string& attribute,
                         const std::string& remediation);
        void synchronize_output();

        PIDAutoTunerConfig config_;
        PIDAutoTunerOutput* output_{nullptr};
        Controller::PIDControllerConfig tuned_config_;
        AutoTunerState state_{AutoTunerState::IDLE};
        PIDAutoTunerAlgorithmState algorithm_state_{PIDAutoTunerAlgorithmState::IDLE};
        double baseline_sensor_{0.0};
        double tuning_start_time_sec_{0.0};
        double step_start_time_sec_{0.0};
        double evaluation_start_time_sec_{0.0};
        double integral_error_{0.0};
        double previous_evaluation_error_{0.0};
        double maximum_tracking_error_{0.0};
        std::size_t tuning_iteration_{0};
        bool have_sensor_input_{false};
        bool evaluation_started_{false};
    };
}  // namespace fast::rf::NavigationSystem::ControllerTuner