#include <Controller/PIDController/PIDController.hpp>
namespace fast::rf::NavigationSystem::Controller {
    bool PIDController::init(IControllerConfig* config) {
        auto* config_ = dynamic_cast<PIDControllerConfig*>(config);
        if (!config_) {
            return false;
        }
        bool status = BaseController::init(config);
        output_ = new PIDControllerOutput();
        return status;
    }
    bool PIDController::new_set_point(double set_point, double time_stamp_sec) {
        return BaseController::new_set_point(set_point, time_stamp_sec);
    }
    bool PIDController::new_sensor_input(double sensor_input, double time_stamp_sec) {
        auto config = dynamic_cast<PIDControllerConfig*>(config_);
        bool status = BaseController::new_sensor_input(sensor_input, time_stamp_sec);
        if (status == false) {
            return false;
        }
        output_->is_new = true;
        output_->setpoint_sensor_error = latest_set_point - (config->sensor_scale * latest_sensor_input);
        output_->P_term = config->K_P * output_->setpoint_sensor_error;
        output_->I_term = config->K_I * 0.0;  // Fill this in
        output_->D_term = config->K_D * 0.0;  // Fill this in
        output_->command_value = output_->P_term + output_->I_term + output_->D_term;
        return true;
    }
    bool PIDController::update(double current_time_sec) { return BaseController::update(current_time_sec); }
    PIDControllerOutput* PIDController::get_output() {
        PIDControllerOutput* output = new PIDControllerOutput(*output_);
        output_->is_new = false;

        return output;
    }
    std::string PIDController::pretty() {
        auto config = dynamic_cast<PIDControllerConfig*>(config_);
        std::string str = "---PID Controller---\n";
        str += BaseController::pretty();
        str += "K: P: " + std::to_string(config->K_P) + " I: " + std::to_string(config->K_I) +
               " D: " + std::to_string(config->K_D) + "\n";
        str += "\tOutput:\n";
        str +=
            "\t\tIs New: " + std::to_string(output_->is_new) + " Cmd: " + std::to_string(output_->command_value) + "\n";
        str += "\t\tError: " + std::to_string(output_->setpoint_sensor_error) + "\n";
        return str;
    }
}  // namespace fast::rf::NavigationSystem::Controller