#include <JoystickScaler.hpp>
namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem {
    bool JoystickScaler::init(ControlDevice device, JoystickCalibrationData joy_calibration_data) {
        if ((device == ControlDevice::UNKNOWN) || (device == ControlDevice::END_OF_LIST)) {
            return false;
        }
        joy_cal_data = joy_calibration_data;
        control_device = device;
        is_initialized = true;
        return true;
    }
    fast::rf::messages::SensorMsgs::JoyMsg JoystickScaler::new_joy(fast::rf::messages::SensorMsgs::JoyMsg joy) {
        fast::rf::messages::SensorMsgs::JoyMsg out_joy;
        if (is_initialized == false) {
            return out_joy;
        }

        // Run Calibration
        // Do X Axis
        if (joy.axes[0] >= (joy_cal_data.x_deadband / 2.0)) {
            joy.axes[0] = scale_value(joy.axes[0], 0.0, 1.0, 0.0, joy_cal_data.x_max);
        } else if (joy.axes[0] <= (-1.0 * joy_cal_data.x_deadband / 2.0)) {
            joy.axes[0] = scale_value(joy.axes[0], -1.0, 0.0, joy_cal_data.x_min, 0.0);
        } else {
            joy.axes[0] = 0.0;
        }
        // Do Y Axis
        if (joy.axes[1] >= (joy_cal_data.y_deadband / 2.0)) {
            joy.axes[1] = scale_value(joy.axes[1], 0.0, 1.0, 0.0, joy_cal_data.y_max);
        } else if (joy.axes[1] <= (-1.0 * joy_cal_data.y_deadband / 2.0)) {
            joy.axes[1] = scale_value(joy.axes[1], -1.0, 0.0, joy_cal_data.y_min, 0.0);
        } else {
            joy.axes[1] = 0.0;
        }
        out_joy.axes.resize(joy.axes.size());
        if (control_device == ControlDevice::THRUSTMASTER_JOYSTICK) {
            for (std::size_t i = 0; i < joy.axes.size(); ++i) {
                out_joy.axes[i] = AXIS_MAX_VALUE * joy.axes[i];
                if (out_joy.axes[i] > AXIS_MAX_VALUE) {
                    out_joy.axes[i] = AXIS_MAX_VALUE;
                } else if (out_joy.axes[i] < (-1.0 * AXIS_MAX_VALUE)) {
                    out_joy.axes[i] = -1.0 * AXIS_MAX_VALUE;
                }
            }
        }
        return out_joy;
    }
    double JoystickScaler::scale_value(double input_value, double input_min, double input_max, double output_min,
                                       double output_max) {
        // Compute Slope: y2-y1/x2-x1
        double m = (output_max - output_min) / (input_max - input_min);
        // Compute new value: y-y1=m(x-x1) --> y = m(x-x1)+y1
        double out = m * (input_value - input_min) + output_min;
        return out;
    }
}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem