#include <BasicTeleopControlProcess/TwistComputer.hpp>
namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem {
    bool TwistComputer::set_config(double max_forward_x_velocity, double max_reverse_x_velocity,
                                   double max_angular_z_velocity, double min_angular_z_velocity) {
        // Forward Velocity Checks
        if (max_forward_x_velocity < max_reverse_x_velocity) {
            return false;
        }

        // Angular Velocity Checks
        if (max_angular_z_velocity < min_angular_z_velocity) {
            return false;
        }

        max_forward_x_velocity_ = max_forward_x_velocity;
        max_reverse_x_velocity_ = max_reverse_x_velocity;
        max_angular_z_velocity_ = max_angular_z_velocity;
        min_angular_z_velocity_ = min_angular_z_velocity;
        return true;
    }
    fast::rf::messages::GeometryMsgs::TwistMsg TwistComputer::new_joy([
        [maybe_unused]] fast::rf::messages::SensorMsgs::JoyMsg joy) {
        fast::rf::messages::GeometryMsgs::TwistMsg twist;
        if (joy.axes.size() < 3) {
            return twist;
        }
        twist.angular.z = joy.axes[0];
        twist.linear.x = joy.axes[1];
        return twist;
    }
}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem