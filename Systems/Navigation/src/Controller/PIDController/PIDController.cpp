#include <Controller/PIDController/PIDController.hpp>
namespace fast::rf::NavigationSystem::Controller {
    bool PIDController::init() {
        bool status = BaseController::init();
        output_ = new PIDControllerOutput();
        return status;
    }
    bool PIDController::new_set_point(double set_point, double time_stamp_sec) {
        return BaseController::new_set_point(set_point, time_stamp_sec);
    }
    bool PIDController::new_sensor_input(double sensor_input, double time_stamp_sec) {
        bool status = BaseController::new_sensor_input(sensor_input, time_stamp_sec);
        if (status == false) {
            return false;
        }
        output_->is_new = true;
        double prev_error = output_->setpoint_sensor_error;
        output_->setpoint_sensor_error = latest_set_point - (config_.get_sensor_scale() * latest_sensor_input);
        I_acc += output_->setpoint_sensor_error * get_sensor_delta_time_sec();

        output_->P_term = config_.get_K_P() * output_->setpoint_sensor_error;
        output_->I_term = config_.get_K_I() * I_acc;
        if (get_sensor_delta_time_sec() > 0.0) {
            double delta_error = (output_->setpoint_sensor_error - prev_error);
            output_->D_term = config_.get_K_D() * delta_error / get_sensor_delta_time_sec();
        }
        double value = output_->P_term + output_->I_term + output_->D_term;
        output_->command_value =
            BaseController::process_command_value(value, config_.get_max_output(), config_.get_min_output());
        return true;
    }
    bool PIDController::update(double current_time_sec) { return BaseController::update(current_time_sec); }
    PIDControllerOutput* PIDController::get_output() {
        PIDControllerOutput* output = new PIDControllerOutput(*output_);
        output_->is_new = false;

        return output;
    }
    std::string PIDController::pretty() {
        std::string str = "\n---PID Controller---\n";
        str += BaseController::pretty();
        str += config_.pretty();
        str += "\tOutput:\n";
        str +=
            "\t\tIs New: " + std::to_string(output_->is_new) + " Cmd: " + std::to_string(output_->command_value) + "\n";
        str += "\t\tError: " + std::to_string(output_->setpoint_sensor_error) + "\n";
        str += "\t\tI Acc: " + std::to_string(I_acc) + "\n";
        return str;
    }
}  // namespace fast::rf::NavigationSystem::Controller