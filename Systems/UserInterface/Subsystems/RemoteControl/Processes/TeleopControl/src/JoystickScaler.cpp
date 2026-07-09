#include <JoystickScaler.hpp>
namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem {
    fast::rf::messages::SensorMsgs::JoyMsg JoystickScaler::new_joy(fast::rf::messages::SensorMsgs::JoyMsg joy) {
        fast::rf::messages::SensorMsgs::JoyMsg out_joy;
        out_joy.axes.reserve(joy.axes.size());
        // Thrustmaster Config
        for (std::size_t i = 0; i < joy.axes.size(); ++i) {
            out_joy.axes[i] = 100.0 * joy.axes[i];
        }
        return out_joy;
    }
}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem