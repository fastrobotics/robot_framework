#include <JoystickScaler.hpp>
namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem {
    bool JoystickScaler::init(ControlDevice device) {
        if ((device != ControlDevice::UNKNOWN) && (device != ControlDevice::END_OF_LIST)) {
            control_device = device;
            is_initialized = true;
            return true;
        }
        return false;
    }
    fast::rf::messages::SensorMsgs::JoyMsg JoystickScaler::new_joy(fast::rf::messages::SensorMsgs::JoyMsg joy) {
        fast::rf::messages::SensorMsgs::JoyMsg out_joy;
        if (is_initialized == false) {
            return out_joy;
        }
        out_joy.axes.resize(joy.axes.size());
        if (control_device == ControlDevice::THRUSTMASTER_JOYSTICK) {
            for (std::size_t i = 0; i < joy.axes.size(); ++i) {
                out_joy.axes[i] = 100.0 * joy.axes[i];
            }
        }
        return out_joy;
    }
}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem