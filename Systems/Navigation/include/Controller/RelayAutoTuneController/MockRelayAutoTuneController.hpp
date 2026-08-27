#pragma once
#include <Controller/RelayAutoTuneController/RelayAutoTuneController.hpp>

namespace fast::rf::NavigationSystem::Controller {
    class MockRelayAutoTuneController : public BaseController {
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

        void set_mock_gains(double K_P, double K_I, double K_D);
        void set_mock_gain_step(double K_P_step, double K_I_step, double K_D_step);
        void set_mock_set_point(double set_point, double set_point_step);
        void set_mock_limits(double set_point_min, double set_point_max, double K_P_min, double K_P_max, double K_I_min,
                             double K_I_max, double K_D_min, double K_D_max);

       private:
        void synchronize_output();

        RelayAutoTuneControllerConfig config_;
        RelayAutoTuneControllerOutput* output_{nullptr};
        PIDControllerConfig tuned_config_;
        RelayAutoTuneState state_{RelayAutoTuneState::IDLE};
        double start_time{0.0};
        double run_time{-1.0};
        double mock_K_P_{0.0};
        double mock_K_I_{0.0};
        double mock_K_D_{0.0};
        double mock_K_P_step_{0.1};
        double mock_K_I_step_{0.01};
        double mock_K_D_step_{0.01};
        double mock_K_P_min_{0.0};
        double mock_K_P_max_{10.0};
        double mock_K_I_min_{0.0};
        double mock_K_I_max_{10.0};
        double mock_K_D_min_{0.0};
        double mock_K_D_max_{10.0};
        double mock_set_point_{0.0};
        double mock_set_point_step_{0.0};
        double mock_set_point_min_{0.0};
        double mock_set_point_max_{100.0};
    };
}  // namespace fast::rf::NavigationSystem::Controller