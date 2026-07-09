#include <JoystickMapper.hpp>
namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem {
    bool JoystickMapper::init(ControlDevice device) {
        if ((device != ControlDevice::UNKNOWN) && (device != ControlDevice::END_OF_LIST)) {
            control_device = device;
            is_initialized = true;
            return true;
        }
        return false;
    }
    fast::rf::messages::SensorMsgs::JoyMsg JoystickMapper::new_joy(fast::rf::messages::SensorMsgs::JoyMsg joy) {
        fast::rf::messages::SensorMsgs::JoyMsg out_joy;
        if (is_initialized == false) {
            return out_joy;
        }

        out_joy.axes.resize(AXIS_COUNT);
        if (joy.axes.size() < AXIS_COUNT) {
            return out_joy;
        }
        if (control_device == ControlDevice::THRUSTMASTER_JOYSTICK) {
            out_joy.axes[0] = joy.axes[0];  // X-Axis
            out_joy.axes[1] = joy.axes[1];  // Y-Axis
            out_joy.axes[2] = joy.axes[2];  // Throttle
        }
        return out_joy;
    }
}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem