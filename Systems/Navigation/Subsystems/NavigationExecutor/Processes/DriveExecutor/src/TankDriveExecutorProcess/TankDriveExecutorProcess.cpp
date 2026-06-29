#include <TankDriveExecutorProcess/TankDriveExecutorProcess.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
bool TankDriveExecutorProcess::update(double current_time_sec, double delta_time_sec) {
    bool status = BaseDriveExecutorProcess::base_update(current_time_sec, delta_time_sec);
    printf("Tank Drive Update Loop");
    if (status == false) {
        return false;
    }
    return true;
}

IDriveExecutorOutput* TankDriveExecutorProcess::new_cmd(GeometryMsgs::TwistMsg cmd) {
    TankDriveData data = convert(cmd);
    output->left_drive = data.left_channel;
    output->right_drive = data.right_channel;
    return output;
}
TankDriveData TankDriveExecutorProcess::convert(GeometryMsgs::TwistMsg twist) {
    TankDriveData data;
    // Invert Rotate due to Right Handle Rule Conventions
    double inverted_rotate = -1.0 * twist.angular.z;

    // Throttle/Steer Mixing
    double left_mixed = twist.linear.x + inverted_rotate;
    double right_mixed = twist.linear.x - inverted_rotate;

    // Invert Right Channel
    double right_inverted = -1.0 * right_mixed;

    // Scale back to Output Range
    double m_left = left_channel_config.max_value - left_channel_config.min_value / 2.0;
    double m_right = right_channel_config.max_value - right_channel_config.min_value / 2.0;

    double b_left = left_channel_config.neutral_value - (m_left * 0.0);
    double b_right = right_channel_config.neutral_value - (m_right * 0.0);

    double left_scaled = left_mixed * m_left + b_left;
    double right_scaled = right_inverted * m_right + b_right;

    // Clip to Min/Max
    double left_clipped = left_scaled;
    if (left_channel_config.max_value > left_channel_config.min_value) {
        left_clipped = clip(left_clipped, left_channel_config.min_value, left_channel_config.max_value);
    } else {
        left_clipped = clip(left_clipped, left_channel_config.max_value, left_channel_config.min_value);
    }

    double right_clipped = right_scaled;
    if (right_channel_config.max_value > right_channel_config.min_value) {
        right_clipped = clip(right_clipped, right_channel_config.min_value, right_channel_config.max_value);
    } else {
        right_clipped = clip(right_clipped, right_channel_config.max_value, right_channel_config.min_value);
    }

    data.left_channel = left_clipped;
    data.right_channel = right_clipped;
    return data;
}
double TankDriveExecutorProcess::clip(double value, double min_value, double max_value) {
    double output = value;
    if (value > max_value) {
        output = max_value;
    }
    if (value < min_value) {
        output = min_value;
    }
    return output;
}
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem