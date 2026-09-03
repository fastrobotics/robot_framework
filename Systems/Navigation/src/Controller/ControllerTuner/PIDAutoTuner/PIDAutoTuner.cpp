#include <ControllerTuner/PIDAutoTuner/PIDAutoTuner.hpp>
#include <cmath>

namespace fast::rf::NavigationSystem::ControllerTuner {
    namespace {
        std::string failure_reason_to_string(PIDAutoTunerFailureReason reason) {
            switch (reason) {
                case PIDAutoTunerFailureReason::INVALID_CONFIGURATION:
                    return "INVALID_CONFIGURATION";
                case PIDAutoTunerFailureReason::RESPONSE_TIMEOUT:
                    return "RESPONSE_TIMEOUT";
                case PIDAutoTunerFailureReason::INSUFFICIENT_RESPONSE:
                    return "INSUFFICIENT_RESPONSE";
                case PIDAutoTunerFailureReason::TRACKING_ERROR_EXCEEDED:
                    return "TRACKING_ERROR_EXCEEDED";
                case PIDAutoTunerFailureReason::TUNING_ITERATION_LIMIT:
                    return "TUNING_ITERATION_LIMIT";
                case PIDAutoTunerFailureReason::UNSUPPORTED_ALGORITHM:
                    return "UNSUPPORTED_ALGORITHM";
                case PIDAutoTunerFailureReason::NONE:
                default:
                    return "NONE";
            }
        }
    }  // namespace
    /**
     * @todo Restructure this to make it easier to read.  Print out what check is failing.  Don't do float compare
     * equality tests like this.
     */
    bool PIDAutoTunerConfig::is_ok() {
        bool any_error = false;
        if (!parameters_set_) {
            fast::rf::Logger::logError("Parameters not set!");
            any_error = true;
        }
        if (!tuning_parameters_set_) {
            fast::rf::Logger::logError("Tuning parameters not set!");
            any_error = true;
        }
        if (max_output_ <= min_output_) {
            fast::rf::Logger::logError("Max Output < Min Output!");
            any_error = true;
        }
        if (output_step_ == 0.0) {
            fast::rf::Logger::logError("Output Step is 0!");
            any_error = true;
        }
        if (set_point_step_ == 0.0) {
            fast::rf::Logger::logError("Set point step is 0!");
            any_error = true;
        }
        if (settle_time_sec_ == 0.0) {
            fast::rf::Logger::logError("Settle time is 0!");
            any_error = true;
        }
        if (response_timeout_sec_ == 0.0) {
            fast::rf::Logger::logError("Response time is 0!");
            any_error = true;
        }
        if (response_timeout_sec_ < settle_time_sec_) {
            fast::rf::Logger::logError("Response Time < Settle Time!");
            any_error = true;
        }
        if (minimum_response_ == 0.0) {
            fast::rf::Logger::logError("Minimum Response is 0!");
            any_error = true;
        }
        if (acceptable_error_threshold_ <= 0.0) {
            fast::rf::Logger::logError("Acceptable Error Threshold <= 0!");
            any_error = true;
        }
        if (evaluation_time_sec_ <= 0.0) {
            fast::rf::Logger::logError("Evalutation Time <= 0!");
            any_error = true;
        }
        if (max_tuning_iterations_ == 0) {
            fast::rf::Logger::logError("Max Tuning Iterations == 0!");
            any_error = true;
        }
        if (sensor_scale_ == 0.0) {
            fast::rf::Logger::logError("Sensor Scale == 0!");
            any_error = true;
        }
        if (algorithm_ == PIDAutoTuningAlgorithm::UNKNOWN) {
            fast::rf::Logger::logError("Unknown Tuning Algorithm!");
            any_error = true;
        }
        if (dead_time_sec_ < 0.0) {
            fast::rf::Logger::logError("Dead Time < 0!");
            any_error = true;
        }
        if (algorithm_ == PIDAutoTuningAlgorithm::IMC_LAMBDA && lambda_sec_ <= 0.0) {
            fast::rf::Logger::logError("Lambda < 0!");
            any_error = true;
        }
        if (output_step_ > max_output_) {
            fast::rf::Logger::logError("Output Step > Max Output!");
            any_error = true;
        }
        if (output_step_ < min_output_) {
            fast::rf::Logger::logError("Output Step < Min Output!");
            any_error = true;
        }
        if (any_error) {
            fast::rf::Logger::logError("Invalid Configuration!");
            return false;
        }
        return true;
    }

    std::string PIDAutoTunerConfig::pretty() {
        return "Output Step: " + std::to_string(output_step_) + " Set Point Step: " + std::to_string(set_point_step_) +
               " Settle Time: " + std::to_string(settle_time_sec_) +
               " Response Timeout: " + std::to_string(response_timeout_sec_) +
               " Minimum Response: " + std::to_string(minimum_response_) +
               " Acceptable Error: " + std::to_string(acceptable_error_threshold_) +
               " Evaluation Time: " + std::to_string(evaluation_time_sec_) +
               " Max Iterations: " + std::to_string(max_tuning_iterations_) +
               " Algorithm: " + std::to_string(static_cast<int>(algorithm_)) + "\n";
    }

    bool PIDAutoTuner::init() {
        bool status = Controller::BaseController::init();
        delete output_;
        output_ = new PIDAutoTunerOutput();
        clear();
        return status;
    }

    bool PIDAutoTuner::set_config(PIDAutoTunerConfig config) {
        if (!config.is_ok()) {
            return false;
        }
        config_ = config;
        return true;
    }

    bool PIDAutoTuner::new_set_point(double set_point, double time_stamp_sec) {
        bool status = Controller::BaseController::new_set_point(set_point, time_stamp_sec);
        if (status && output_ != nullptr) {
            output_->set_point = set_point;
        }
        return status;
    }

    bool PIDAutoTuner::new_sensor_input(double sensor_input, double time_stamp_sec) {
        bool status = Controller::BaseController::new_sensor_input(sensor_input, time_stamp_sec);
        if (!status || output_ == nullptr) {
            return status;
        }
        output_->sensor_input = config_.get_sensor_scale() * sensor_input;
        have_sensor_input_ = true;
        if (state_ == AutoTunerState::TUNING && algorithm_state_ == PIDAutoTunerAlgorithmState::CAPTURE_BASELINE) {
            baseline_sensor_ = output_->sensor_input;
            output_->set_point = baseline_sensor_ + config_.get_set_point_step();
            algorithm_state_ = PIDAutoTunerAlgorithmState::APPLY_STEP;
            output_->algorithm_state = algorithm_state_;
        }
        output_->is_new = true;
        return true;
    }

    bool PIDAutoTuner::update(double current_time_sec) {
        bool status = Controller::BaseController::update(current_time_sec);
        if (!status || output_ == nullptr) {
            return status;
        }
        if (state_ == AutoTunerState::TUNING) {
            status = run_tuning_step(current_time_sec);
        }
        return status;
    }

    PIDAutoTunerOutput* PIDAutoTuner::get_output() {
        PIDAutoTunerOutput* output = new PIDAutoTunerOutput(*output_);
        output_->is_new = false;
        return output;
    }

    std::string PIDAutoTuner::pretty() {
        return "\n---PID Auto-Tuner---\n" + config_.pretty() + "State: " + std::to_string(static_cast<int>(state_)) +
               " Algorithm State: " + std::to_string(static_cast<int>(algorithm_state_)) +
               " Set Point: " + std::to_string(output_->set_point) +
               " Sensor: " + std::to_string(output_->sensor_input) + " K_P: " + std::to_string(output_->K_P) +
               " K_I: " + std::to_string(output_->K_I) + " K_D: " + std::to_string(output_->K_D) +
               "\nFailure Reason: " + output_->failure_reason_string + " Attribute: " + output_->failure_attribute +
               " Remediation: " + output_->failure_remediation + "\n";
    }

    bool PIDAutoTuner::clear() {
        state_ = AutoTunerState::IDLE;
        algorithm_state_ = PIDAutoTunerAlgorithmState::IDLE;
        baseline_sensor_ = 0.0;
        tuning_start_time_sec_ = 0.0;
        step_start_time_sec_ = 0.0;
        evaluation_start_time_sec_ = 0.0;
        integral_error_ = 0.0;
        previous_evaluation_error_ = 0.0;
        maximum_tracking_error_ = 0.0;
        positive_response_ = 0.0;
        positive_step_complete_ = false;
        evaluation_motion_detected_ = false;
        tuning_iteration_ = 0;
        have_sensor_input_ = false;
        evaluation_started_ = false;
        if (output_ != nullptr) {
            output_->state = state_;
            output_->failure_reason = PIDAutoTunerFailureReason::NONE;
            output_->failure_reason_string = "NONE";
            output_->failure_attribute.clear();
            output_->failure_remediation.clear();
            output_->algorithm_state = algorithm_state_;
            output_->is_new = false;
            output_->command_value = 0.0;
            output_->set_point = 0.0;
            output_->sensor_input = 0.0;
            output_->K_P = 0.0;
            output_->K_I = 0.0;
            output_->K_D = 0.0;
            output_->response = 0.0;
            output_->tracking_error = 0.0;
            output_->maximum_tracking_error = 0.0;
            output_->elapsed_time_sec = 0.0;
        }
        return true;
    }

    bool PIDAutoTuner::start_tuning() {
        if (output_ == nullptr || !config_.is_ok()) {
            fail_tuning(PIDAutoTunerFailureReason::INVALID_CONFIGURATION, "PIDAutoTunerConfig",
                        "Set both parameter groups with valid limits and tuning values before start_tuning().");
            return false;
        }
        state_ = AutoTunerState::TUNING;
        algorithm_state_ = PIDAutoTunerAlgorithmState::CAPTURE_BASELINE;
        tuning_start_time_sec_ = 0.0;
        step_start_time_sec_ = 0.0;
        evaluation_start_time_sec_ = 0.0;
        integral_error_ = 0.0;
        previous_evaluation_error_ = 0.0;
        maximum_tracking_error_ = 0.0;
        positive_response_ = 0.0;
        positive_step_complete_ = false;
        evaluation_motion_detected_ = false;
        tuning_iteration_ = 0;
        have_sensor_input_ = false;
        evaluation_started_ = false;
        output_->state = state_;
        output_->failure_reason = PIDAutoTunerFailureReason::NONE;
        output_->failure_reason_string = "NONE";
        output_->failure_attribute.clear();
        output_->failure_remediation.clear();
        output_->algorithm = config_.get_algorithm();
        output_->algorithm_state = algorithm_state_;
        output_->is_new = true;
        return true;
    }

    bool PIDAutoTuner::run_tuning_step(double current_time_sec) {
        switch (config_.get_algorithm()) {
            case PIDAutoTuningAlgorithm::STEP_RESPONSE:
                return run_step_response_tuning_step(current_time_sec);
            case PIDAutoTuningAlgorithm::IMC_LAMBDA:
                return run_step_response_tuning_step(current_time_sec);
            default:
                fail_tuning(PIDAutoTunerFailureReason::UNSUPPORTED_ALGORITHM, "algorithm",
                            "Select an implemented PIDAutoTuningAlgorithm before starting the tuner.");
                return false;
        }
    }

    bool PIDAutoTuner::run_step_response_tuning_step(double current_time_sec) {
        if (algorithm_state_ == PIDAutoTunerAlgorithmState::CAPTURE_BASELINE) {
            if (!have_sensor_input_) {
                return true;
            }
            algorithm_state_ = PIDAutoTunerAlgorithmState::APPLY_STEP;
            output_->algorithm_state = algorithm_state_;
        }
        if (algorithm_state_ == PIDAutoTunerAlgorithmState::APPLY_STEP) {
            tuning_start_time_sec_ = current_time_sec;
            step_start_time_sec_ = current_time_sec;
            double step_magnitude = std::abs(config_.get_output_step());
            double set_point_magnitude = std::abs(config_.get_set_point_step());
            double step_direction = positive_step_complete_ ? -1.0 : 1.0;
            output_->set_point = baseline_sensor_ + step_direction * set_point_magnitude;
            output_->command_value = Controller::BaseController::process_command_value(
                step_direction * step_magnitude, config_.get_max_output(), config_.get_min_output());
            algorithm_state_ = PIDAutoTunerAlgorithmState::MEASURE_RESPONSE;
            output_->algorithm_state = algorithm_state_;
            output_->is_new = true;
            return true;
        }
        if (algorithm_state_ == PIDAutoTunerAlgorithmState::EVALUATE_PID) {
            double tracking_error = output_->set_point - output_->sensor_input;
            if (!evaluation_started_) {
                evaluation_started_ = true;
                evaluation_start_time_sec_ = current_time_sec;
                previous_evaluation_error_ = tracking_error;
                maximum_tracking_error_ = 0.0;
            } else {
                double sample_time_sec = get_sensor_delta_time_sec();
                if (sample_time_sec > 0.0) {
                    integral_error_ += tracking_error * sample_time_sec;
                }
            }
            double evaluation_elapsed_time = current_time_sec - evaluation_start_time_sec_;
            if (evaluation_elapsed_time >= config_.get_settle_time_sec()) {
                maximum_tracking_error_ = std::max(maximum_tracking_error_, std::abs(tracking_error));
            }
            double derivative_error = tracking_error - previous_evaluation_error_;
            if (get_sensor_delta_time_sec() > 0.0) {
                derivative_error /= get_sensor_delta_time_sec();
            } else {
                derivative_error = 0.0;
            }
            previous_evaluation_error_ = tracking_error;
            output_->tracking_error = tracking_error;
            output_->maximum_tracking_error = maximum_tracking_error_;
            output_->elapsed_time_sec = evaluation_elapsed_time;
            double evaluation_command =
                output_->K_P * tracking_error + output_->K_I * integral_error_ + output_->K_D * derivative_error;
            double minimum_evaluation_command = std::abs(config_.get_output_step());
            if (std::abs(output_->sensor_input - baseline_sensor_) >= config_.get_minimum_response()) {
                evaluation_motion_detected_ = true;
            }
            if (std::abs(tracking_error) <= config_.get_acceptable_error_threshold()) {
                evaluation_command = 0.0;
            } else if (!evaluation_motion_detected_) {
                double set_point_direction = output_->set_point >= baseline_sensor_ ? 1.0 : -1.0;
                evaluation_command = set_point_direction * minimum_evaluation_command;
            }
            output_->command_value = Controller::BaseController::process_command_value(
                evaluation_command, config_.get_max_output(), config_.get_min_output());
            if (output_->elapsed_time_sec >= config_.get_evaluation_time_sec()) {
                if (maximum_tracking_error_ <= config_.get_acceptable_error_threshold()) {
                    state_ = AutoTunerState::COMPLETE;
                    algorithm_state_ = PIDAutoTunerAlgorithmState::COMPLETE;
                    output_->state = state_;
                    output_->algorithm_state = algorithm_state_;
                    output_->command_value = 0.0;
                } else {
                    ++tuning_iteration_;
                    if (tuning_iteration_ >= config_.get_max_tuning_iterations()) {
                        fail_tuning(
                            PIDAutoTunerFailureReason::TUNING_ITERATION_LIMIT, "maximum_tracking_error",
                            "Increase max_tuning_iterations or revise the output step and PID search strategy.");
                        return false;
                    }
                    output_->K_P *= 1.5;
                    output_->K_I *= 1.5;
                    output_->K_D *= 1.5;
                    tuned_config_.set_parameters(config_.get_max_output(), config_.get_min_output(), output_->K_P,
                                                 output_->K_I, output_->K_D, config_.get_sensor_scale());
                    evaluation_started_ = false;
                    integral_error_ = 0.0;
                    previous_evaluation_error_ = 0.0;
                    maximum_tracking_error_ = 0.0;
                    evaluation_motion_detected_ = false;
                    output_->is_new = true;
                    return true;
                }
            }
            output_->is_new = true;
            return true;
        }
        double elapsed_time = current_time_sec - step_start_time_sec_;
        output_->elapsed_time_sec = elapsed_time;
        output_->response = output_->sensor_input - baseline_sensor_;
        if (elapsed_time >= config_.get_settle_time_sec()) {
            double step_magnitude = std::abs(config_.get_output_step());
            double process_gain = output_->response / (positive_step_complete_ ? -step_magnitude : step_magnitude);
            if (std::abs(output_->response) >= config_.get_minimum_response() && std::abs(process_gain) > 0.0) {
                if (!positive_step_complete_) {
                    positive_response_ = output_->response;
                    positive_step_complete_ = true;
                    algorithm_state_ = PIDAutoTunerAlgorithmState::APPLY_STEP;
                    output_->algorithm_state = algorithm_state_;
                    output_->set_point = baseline_sensor_ - std::abs(config_.get_set_point_step());
                    output_->command_value = 0.0;
                    output_->is_new = true;
                    return true;
                }
                process_gain = (positive_response_ / step_magnitude + process_gain) / 2.0;
                double proportional_gain = 1.0 / process_gain;
                double integral_gain = proportional_gain / config_.get_settle_time_sec();
                double derivative_gain = proportional_gain * config_.get_settle_time_sec() * 0.1;
                if (config_.get_algorithm() == PIDAutoTuningAlgorithm::IMC_LAMBDA) {
                    double time_constant_sec = config_.get_settle_time_sec();
                    double lambda_sec = config_.get_lambda_sec();
                    double dead_time_sec = config_.get_dead_time_sec();
                    proportional_gain =
                        (time_constant_sec + 0.5 * dead_time_sec) / (process_gain * (lambda_sec + 0.5 * dead_time_sec));
                    double integral_time_sec = time_constant_sec + 0.5 * dead_time_sec;
                    double derivative_time_sec =
                        (time_constant_sec * dead_time_sec) / (2.0 * time_constant_sec + dead_time_sec);
                    integral_gain = proportional_gain / integral_time_sec;
                    derivative_gain = proportional_gain * derivative_time_sec;
                }
                tuned_config_.set_parameters(config_.get_max_output(), config_.get_min_output(), proportional_gain,
                                             integral_gain, derivative_gain, config_.get_sensor_scale());
                output_->K_P = proportional_gain;
                output_->K_I = integral_gain;
                output_->K_D = derivative_gain;
                algorithm_state_ = PIDAutoTunerAlgorithmState::EVALUATE_PID;
                output_->algorithm_state = algorithm_state_;
                evaluation_started_ = false;
                integral_error_ = 0.0;
                previous_evaluation_error_ = 0.0;
                maximum_tracking_error_ = 0.0;
                output_->is_new = true;
                return true;
            }
        }
        if (elapsed_time >= config_.get_response_timeout_sec()) {
            if (std::abs(output_->response) < config_.get_minimum_response()) {
                fail_tuning(PIDAutoTunerFailureReason::INSUFFICIENT_RESPONSE, "response",
                            "Increase output_step, verify actuator authority, or reduce minimum_response.");
            } else {
                fail_tuning(
                    PIDAutoTunerFailureReason::RESPONSE_TIMEOUT, "elapsed_time_sec",
                    "Verify sensor timestamps and actuator feedback, then increase response_timeout_sec if needed.");
            }
            return false;
        }
        return true;
    }

    void PIDAutoTuner::fail_tuning(PIDAutoTunerFailureReason reason, const std::string& attribute,
                                   const std::string& remediation) {
        state_ = AutoTunerState::FAILED;
        algorithm_state_ = PIDAutoTunerAlgorithmState::FAILED;
        if (output_ != nullptr) {
            output_->state = state_;
            output_->failure_reason = reason;
            output_->failure_reason_string = failure_reason_to_string(reason);
            output_->failure_attribute = attribute;
            output_->failure_remediation = remediation;
            output_->algorithm_state = algorithm_state_;
            output_->command_value = 0.0;
            output_->is_new = true;
        }
    }
}  // namespace fast::rf::NavigationSystem::ControllerTuner
