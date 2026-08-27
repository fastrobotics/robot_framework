#include <Controller/RelayAutoTuneController/MockRelayAutoTuneController.hpp>
#include <cmath>

namespace fast::rf::NavigationSystem::Controller {
    namespace {
        void advance_value(double& value, double& step, double minimum, double maximum) {
            if (step == 0.0) {
                return;
            }
            value += step;
            if (value >= maximum) {
                value = maximum;
                step = -std::abs(step);
            } else if (value <= minimum) {
                value = minimum;
                step = std::abs(step);
            }
        }
    }  // namespace

    bool MockRelayAutoTuneController::init() {
        bool status = BaseController::init();
        delete output_;
        output_ = new RelayAutoTuneControllerOutput();
        clear();
        return status;
    }

    bool MockRelayAutoTuneController::set_config(RelayAutoTuneControllerConfig config) {
        if (!config.is_ok()) {
            return false;
        }
        config_ = config;
        return true;
    }

    bool MockRelayAutoTuneController::new_set_point(double set_point, double time_stamp_sec) {
        mock_set_point_ = set_point;
        return BaseController::new_set_point(set_point, time_stamp_sec);
    }

    bool MockRelayAutoTuneController::new_sensor_input(double sensor_input, double time_stamp_sec) {
        bool status = BaseController::new_sensor_input(sensor_input, time_stamp_sec);
        if (status && output_ != nullptr) {
            synchronize_output();
            output_->is_new = true;
        }
        return status;
    }

    bool MockRelayAutoTuneController::update(double current_time_sec) {
        bool status = BaseController::update(current_time_sec);
        if (status && state_ == RelayAutoTuneState::TUNING) {
            advance_value(mock_K_P_, mock_K_P_step_, mock_K_P_min_, mock_K_P_max_);
            advance_value(mock_K_I_, mock_K_I_step_, mock_K_I_min_, mock_K_I_max_);
            advance_value(mock_K_D_, mock_K_D_step_, mock_K_D_min_, mock_K_D_max_);
            advance_value(mock_set_point_, mock_set_point_step_, mock_set_point_min_, mock_set_point_max_);
            BaseController::new_set_point(mock_set_point_, current_time_sec);
            synchronize_output();
            output_->is_new = true;
        }
        return status;
    }

    RelayAutoTuneControllerOutput* MockRelayAutoTuneController::get_output() {
        RelayAutoTuneControllerOutput* output = new RelayAutoTuneControllerOutput(*output_);
        output_->is_new = false;
        return output;
    }

    std::string MockRelayAutoTuneController::pretty() {
        return "\n---Mock Relay Auto-Tune Controller---\n" + config_.pretty() +
               "Set Point: " + std::to_string(mock_set_point_) + " K_P: " + std::to_string(mock_K_P_) +
               " K_I: " + std::to_string(mock_K_I_) + " K_D: " + std::to_string(mock_K_D_) + "\n";
    }

    bool MockRelayAutoTuneController::clear() {
        state_ = RelayAutoTuneState::IDLE;
        if (output_ != nullptr) {
            output_->state = state_;
            output_->is_new = false;
            output_->command_value = 0.0;
            output_->set_point = 0.0;
            output_->K_P = 0.0;
            output_->K_I = 0.0;
            output_->K_D = 0.0;
        }
        return true;
    }

    bool MockRelayAutoTuneController::start_tuning() {
        if (output_ == nullptr) {
            fast::rf::Logger::log_error("Output is Null!");
            state_ = RelayAutoTuneState::FAILED;
            return false;
        }
        if (!config_.is_ok()) {
            fast::rf::Logger::log_error("onfig is invalid!");
            state_ = RelayAutoTuneState::FAILED;
            return false;
        }
        state_ = RelayAutoTuneState::TUNING;
        output_->state = state_;
        synchronize_output();
        return true;
    }

    void MockRelayAutoTuneController::set_mock_gains(double K_P, double K_I, double K_D) {
        mock_K_P_ = K_P;
        mock_K_I_ = K_I;
        mock_K_D_ = K_D;
        synchronize_output();
    }

    void MockRelayAutoTuneController::set_mock_gain_step(double K_P_step, double K_I_step, double K_D_step) {
        mock_K_P_step_ = K_P_step;
        mock_K_I_step_ = K_I_step;
        mock_K_D_step_ = K_D_step;
    }

    void MockRelayAutoTuneController::set_mock_set_point(double set_point, double set_point_step) {
        mock_set_point_ = set_point;
        mock_set_point_step_ = set_point_step;
        BaseController::new_set_point(set_point, 0.0);
        synchronize_output();
    }

    void MockRelayAutoTuneController::set_mock_limits(double set_point_min, double set_point_max, double K_P_min,
                                                      double K_P_max, double K_I_min, double K_I_max, double K_D_min,
                                                      double K_D_max) {
        mock_set_point_min_ = set_point_min;
        mock_set_point_max_ = set_point_max;
        mock_K_P_min_ = K_P_min;
        mock_K_P_max_ = K_P_max;
        mock_K_I_min_ = K_I_min;
        mock_K_I_max_ = K_I_max;
        mock_K_D_min_ = K_D_min;
        mock_K_D_max_ = K_D_max;
    }

    void MockRelayAutoTuneController::synchronize_output() {
        if (output_ == nullptr) {
            return;
        }
        output_->state = state_;
        output_->set_point = mock_set_point_;
        output_->command_value = mock_set_point_;
        output_->K_P = mock_K_P_;
        output_->K_I = mock_K_I_;
        output_->K_D = mock_K_D_;
        tuned_config_.set_parameters(config_.get_max_output(), config_.get_min_output(), mock_K_P_, mock_K_I_,
                                     mock_K_D_, config_.get_sensor_scale());
    }
}  // namespace fast::rf::NavigationSystem::Controller