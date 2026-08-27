#include <Controller/RelayAutoTuneController/RelayAutoTuneController.hpp>
#include <algorithm>
#include <cmath>
#include <numeric>

namespace fast::rf::NavigationSystem::Controller {
    bool RelayAutoTuneControllerConfig::is_ok() {
        if (max_output_ < min_output_ || relay_amplitude_ <= 0.0 || required_cycles_ < 2 ||
            minimum_period_sec_ <= 0.0 || minimum_response_amplitude_ <= 0.0 ||
            bias_ + relay_amplitude_ > max_output_ || bias_ - relay_amplitude_ < min_output_) {
            fast::rf::Logger::log_error("Invalid relay auto-tune configuration!");
            return false;
        }
        return true;
    }

    std::string RelayAutoTuneControllerConfig::pretty() {
        return "Relay Amplitude: " + std::to_string(relay_amplitude_) + " Bias: " + std::to_string(bias_) +
               " Sensor Scale: " + std::to_string(sensor_scale_) +
               " Required Cycles: " + std::to_string(required_cycles_) + "\n";
    }

    bool RelayAutoTuneController::init() {
        bool status = BaseController::init();
        delete output_;
        output_ = new RelayAutoTuneControllerOutput();
        clear();
        return status;
    }

    bool RelayAutoTuneController::set_config(RelayAutoTuneControllerConfig config) {
        if (!config.is_ok()) {
            fast::rf::Logger::log_error("Error setting relay auto-tune config: " + config.pretty());
            return false;
        }
        config_ = config;
        return true;
    }

    bool RelayAutoTuneController::new_set_point(double set_point, double time_stamp_sec) {
        bool status = BaseController::new_set_point(set_point, time_stamp_sec);
        if (status && output_ != nullptr) {
            output_->set_point = set_point;
        }
        return status;
    }

    bool RelayAutoTuneController::new_sensor_input(double sensor_input, double time_stamp_sec) {
        if (!BaseController::new_sensor_input(sensor_input, time_stamp_sec)) {
            return false;
        }
        if (state_ != RelayAutoTuneState::TUNING) {
            return true;
        }

        double error = latest_set_point - config_.get_sensor_scale() * latest_sensor_input;
        double scaled_sensor = config_.get_sensor_scale() * latest_sensor_input;
        if (have_previous_error_) {
            bool rising_crossing = previous_error_ <= 0.0 && error > 0.0;
            bool falling_crossing = previous_error_ >= 0.0 && error < 0.0;
            if (rising_crossing || falling_crossing) {
                if (have_previous_crossing_ &&
                    time_stamp_sec - previous_crossing_sec_ < 0.5 * config_.get_minimum_period_sec()) {
                    fail_tuning();
                    return false;
                }
                previous_crossing_sec_ = time_stamp_sec;
                have_previous_crossing_ = true;
                if (rising_crossing) {
                    if (have_previous_rising_crossing_) {
                        periods_.push_back(time_stamp_sec - previous_rising_crossing_sec_);
                        if (periods_.size() >= config_.get_required_cycles()) {
                            response_min_ = std::min(response_min_, scaled_sensor);
                            response_max_ = std::max(response_max_, scaled_sensor);
                            return finish_tuning();
                        }
                    }
                    previous_rising_crossing_sec_ = time_stamp_sec;
                    have_previous_rising_crossing_ = true;
                }
                response_min_ = scaled_sensor;
                response_max_ = scaled_sensor;
            } else if (have_previous_rising_crossing_) {
                response_min_ = std::min(response_min_, scaled_sensor);
                response_max_ = std::max(response_max_, scaled_sensor);
            }
        }
        previous_error_ = error;
        have_previous_error_ = true;
        output_->command_value =
            BaseController::process_command_value(error >= 0.0 ? config_.get_bias() + config_.get_relay_amplitude()
                                                               : config_.get_bias() - config_.get_relay_amplitude(),
                                                  config_.get_max_output(), config_.get_min_output());
        output_->is_new = true;
        return true;
    }

    bool RelayAutoTuneController::update(double current_time_sec) { return BaseController::update(current_time_sec); }

    RelayAutoTuneControllerOutput* RelayAutoTuneController::get_output() {
        RelayAutoTuneControllerOutput* output = new RelayAutoTuneControllerOutput(*output_);
        output_->is_new = false;
        return output;
    }

    std::string RelayAutoTuneController::pretty() {
        return "\n---Relay Auto-Tune Controller---\n" + config_.pretty() +
               "State: " + std::to_string(static_cast<int>(state_)) +
               " Ultimate Gain: " + std::to_string(output_->ultimate_gain) +
               " Ultimate Period: " + std::to_string(output_->ultimate_period_sec) + "\n";
    }

    bool RelayAutoTuneController::clear() {
        state_ = RelayAutoTuneState::IDLE;
        reset_measurements();
        if (output_ != nullptr) {
            output_->state = state_;
            output_->is_new = false;
            output_->command_value = 0.0;
            output_->set_point = 0.0;
            output_->K_P = 0.0;
            output_->K_I = 0.0;
            output_->K_D = 0.0;
            output_->ultimate_gain = 0.0;
            output_->ultimate_period_sec = 0.0;
            output_->response_amplitude = 0.0;
        }
        return true;
    }

    bool RelayAutoTuneController::start_tuning() {
        if (output_ == nullptr || !config_.is_ok()) {
            fail_tuning();
            return false;
        }
        reset_measurements();
        state_ = RelayAutoTuneState::TUNING;
        output_->state = state_;
        return true;
    }

    bool RelayAutoTuneController::finish_tuning() {
        double average_period = std::accumulate(periods_.begin(), periods_.end(), 0.0) / periods_.size();
        double response_amplitude = 0.5 * (response_max_ - response_min_);
        bool periods_are_valid = std::all_of(periods_.begin(), periods_.end(), [this](double period) {
            return period >= config_.get_minimum_period_sec();
        });
        if (!periods_are_valid || response_amplitude < config_.get_minimum_response_amplitude()) {
            fail_tuning();
            return false;
        }

        double ultimate_gain = 4.0 * config_.get_relay_amplitude() / (M_PI * response_amplitude);
        tuned_config_.set_parameters(config_.get_max_output(), config_.get_min_output(), 0.6 * ultimate_gain,
                                     1.2 * ultimate_gain / average_period, 0.075 * ultimate_gain * average_period,
                                     config_.get_sensor_scale());
        output_->set_point = latest_set_point;
        output_->K_P = tuned_config_.get_K_P();
        output_->K_I = tuned_config_.get_K_I();
        output_->K_D = tuned_config_.get_K_D();
        output_->ultimate_gain = ultimate_gain;
        output_->ultimate_period_sec = average_period;
        output_->response_amplitude = response_amplitude;
        state_ = RelayAutoTuneState::COMPLETE;
        output_->state = state_;
        output_->command_value = config_.get_bias();
        output_->is_new = true;
        return true;
    }

    void RelayAutoTuneController::fail_tuning() {
        state_ = RelayAutoTuneState::FAILED;
        if (output_ != nullptr) {
            output_->state = state_;
            output_->command_value = 0.0;
            output_->is_new = true;
        }
    }

    void RelayAutoTuneController::reset_measurements() {
        have_previous_error_ = false;
        have_previous_rising_crossing_ = false;
        have_previous_crossing_ = false;
        previous_error_ = 0.0;
        previous_rising_crossing_sec_ = 0.0;
        previous_crossing_sec_ = 0.0;
        response_min_ = 0.0;
        response_max_ = 0.0;
        periods_.clear();
    }
}  // namespace fast::rf::NavigationSystem::Controller
