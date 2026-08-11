#include <Controller/BaseController.hpp>
namespace fast::rf::NavigationSystem::Controller {
    bool BaseController::init(IControllerConfig* config) {
        if (config == nullptr) {
            return false;
        }
        config_ = config;
        return true;
    }
    bool BaseController::new_set_point(double set_point, [[maybe_unused]] double time_stamp_sec) {
        latest_set_point = set_point;
        setpoint_rx_count++;
        return true;
    }
    bool BaseController::new_sensor_input(double sensor_input, double time_stamp_sec) {
        if (sensor_rx_count > 0) {
            delta_sensor_sample_time_sec = (time_stamp_sec - sensor_timestamp_sec_);
        }
        sensor_timestamp_sec_ = time_stamp_sec;
        latest_sensor_input = sensor_input;
        sensor_rx_count++;
        return true;
    }
    bool BaseController::update(double current_time_sec) {
        current_time_sec_ = current_time_sec;
        update_count++;
        return true;
    }
    double BaseController::process_command_value(double command_value) {
        if (command_value > config_->max_output) {
            command_value = config_->max_output;
        } else if (command_value < config_->min_output) {
            command_value = config_->min_output;
        }
        return command_value;
    }
    std::string BaseController::pretty() {
        std::string str = "---Base Controller---\n";
        str += "\tMax Command: " + std::to_string(config_->max_output) +
               " Min Command: " + std::to_string(config_->min_output) + "\n";
        str += "\tController Type: " + std::to_string((uint8_t)controller_type) + "\n";
        str += "\tLatest Set Point: " + std::to_string(latest_set_point) +
               " Sensor Input: " + std::to_string(latest_sensor_input) + "\n";
        if (get_sensor_delta_time_sec() > 0.0) {
            str += "\tSensor Delta Time: " + std::to_string(1000.0 * get_sensor_delta_time_sec()) + " (mS)" + "\n";
        }

        str += "\tCounts:\n";
        str += "\t\tUpdate: " + std::to_string(update_count) + "\n";
        str += "\t\tSensor Rx: " + std::to_string(sensor_rx_count) + "\n";
        str += "\t\tSet Point Rx: " + std::to_string(setpoint_rx_count) + "\n";
        return str;
    }
}  // namespace fast::rf::NavigationSystem::Controller