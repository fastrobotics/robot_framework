#pragma once
#include <Controller/BaseController.hpp>
#include <Controller/PIDController/PIDController.hpp>
#include <cstddef>
#include <vector>

namespace fast::rf::NavigationSystem::Controller {
    enum class RelayAutoTuneState { IDLE, TUNING, COMPLETE, FAILED };

    class RelayAutoTuneControllerConfig : public IControllerConfig {
       public:
        ~RelayAutoTuneControllerConfig() override {}

        void set_parameters(double max_output, double min_output, double relay_amplitude, double bias,
                            double sensor_scale_factor, std::size_t required_cycles, double minimum_period_sec = 0.1,
                            double minimum_response_amplitude = 1.0e-3) {
            max_output_ = max_output;
            min_output_ = min_output;
            relay_amplitude_ = relay_amplitude;
            bias_ = bias;
            sensor_scale_ = sensor_scale_factor;
            required_cycles_ = required_cycles;
            minimum_period_sec_ = minimum_period_sec;
            minimum_response_amplitude_ = minimum_response_amplitude;
        }

        bool is_ok() override;
        std::string pretty() override;
        double get_relay_amplitude() const { return relay_amplitude_; }
        double get_bias() const { return bias_; }
        double get_sensor_scale() const { return sensor_scale_; }
        std::size_t get_required_cycles() const { return required_cycles_; }
        double get_minimum_period_sec() const { return minimum_period_sec_; }
        double get_minimum_response_amplitude() const { return minimum_response_amplitude_; }

       private:
        double relay_amplitude_{1.0};
        double bias_{0.0};
        double sensor_scale_{1.0};
        std::size_t required_cycles_{4};
        double minimum_period_sec_{0.1};
        double minimum_response_amplitude_{1.0e-3};
    };

    class RelayAutoTuneControllerOutput : public IControllerOutput {
       public:
        ~RelayAutoTuneControllerOutput() override {}
        RelayAutoTuneState state{RelayAutoTuneState::IDLE};
        double set_point{0.0};
        double K_P{0.0};
        double K_I{0.0};
        double K_D{0.0};
        double ultimate_gain{0.0};
        double ultimate_period_sec{0.0};
        double response_amplitude{0.0};
    };

    class RelayAutoTuneController : public BaseController {
       public:
        ControllerType get_controller_type() override { return ControllerType::RELAY_AUTO_TUNE_CONTROLLER; }
        bool init() override;
        bool set_config(RelayAutoTuneControllerConfig config);
        bool new_set_point(double set_point, double time_stamp_sec) override;
        bool new_sensor_input(double sensor_input, double time_stamp_sec) override;
        bool update(double current_time_sec) override;
        RelayAutoTuneControllerOutput* get_output() override;
        std::string pretty() override;
        bool clear() override;

        bool start_tuning();
        bool is_tuning_complete() const { return state_ == RelayAutoTuneState::COMPLETE; }
        bool tuning_succeeded() const { return is_tuning_complete(); }
        PIDControllerConfig get_tuned_config() const { return tuned_config_; }
        RelayAutoTuneState get_state() const { return state_; }

       private:
        bool finish_tuning();
        void fail_tuning();
        void reset_measurements();

        RelayAutoTuneControllerConfig config_;
        RelayAutoTuneControllerOutput* output_{nullptr};
        PIDControllerConfig tuned_config_;
        RelayAutoTuneState state_{RelayAutoTuneState::IDLE};
        bool have_previous_error_{false};
        bool have_previous_rising_crossing_{false};
        double previous_error_{0.0};
        double previous_rising_crossing_sec_{0.0};
        double response_min_{0.0};
        double response_max_{0.0};
        std::vector<double> periods_;
    };
}  // namespace fast::rf::NavigationSystem::Controller
