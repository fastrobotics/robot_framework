#include <JoystickMapper.hpp>
namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem {
    fast::rf::messages::SensorMsgs::JoyMsg JoystickMapper::new_joy(fast::rf::messages::SensorMsgs::JoyMsg joy) {
        fast::rf::messages::SensorMsgs::JoyMsg out_joy;
        // For Thrustmaster Joystick
        out_joy.axes.resize(AXIS_COUNT);
        if (joy.axes.size() < AXIS_COUNT) {
            return out_joy;
        }
        out_joy.axes[0] = joy.axes[0];  // X-Axis
        out_joy.axes[1] = joy.axes[1];  // Y-Axis
        out_joy.axes[2] = joy.axes[2];  // Throttle
        return joy;
    }
}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem