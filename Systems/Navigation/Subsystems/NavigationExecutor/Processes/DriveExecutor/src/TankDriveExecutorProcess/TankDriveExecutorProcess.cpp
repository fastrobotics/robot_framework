#include <TankDriveExecutorProcess/TankDriveExecutorProcess.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::DriveExecutor {
    bool TankDriveExecutorProcess::init() {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::REMOTE_CONTROL);
        bool status = diagnosticManager.initializeDiagnostics(diagnostic_types);

        diagnosticManager.updateDiagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE,
                                           fast::rf::Level::NOERROR,
                                           fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "SW Running.");

        diagnosticManager.updateDiagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::REMOTE_CONTROL, fast::rf::Level::WARN,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NODATA, "Waiting for R/C Command.");

        return status;
    }
    bool TankDriveExecutorProcess::update(double current_time_sec) {
        bool status = BaseDriveExecutorProcess::update(current_time_sec);
        // GCOV_EXCL_START
        // This will always be ok
        if (status == false) {
            return false;
        }
        // GCOV_EXCL_STOP
        return true;
    }
    std::string TankDriveExecutorProcess::pretty() {
        std::string str = "\n---Tank Drive Executor Process---";
        str += BaseDriveExecutorProcess::pretty();
        return str;
    }

    IDriveExecutorOutput* TankDriveExecutorProcess::new_cmd(GeometryMsgs::TwistMsg cmd) {
        TankDriveData data = convert(cmd);
        output->left_drive = data.left_channel;
        output->right_drive = data.right_channel;
        diagnosticManager.updateDiagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::REMOTE_CONTROL, fast::rf::Level::NOERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "R/C Command Updated.");
        return output.get();
    }
    TankDriveData TankDriveExecutorProcess::convert(GeometryMsgs::TwistMsg twist) {
        TankDriveData data;
        // Normalize to [-1.0,1.0]
        double input_forward_normalized = twist.linear.x / 100.0;
        double input_rotate_normalized = twist.angular.z / 100.0;

        // Invert Rotate due to Right Handle Rule Conventions
        double inverted_rotate = -1.0 * input_rotate_normalized;

        // Throttle/Steer Mixing
        double left_mixed = input_forward_normalized + inverted_rotate;
        double right_mixed = input_forward_normalized - inverted_rotate;

        // Invert Right Channel
        double right_inverted = -1.0 * right_mixed;

        // Scale back to Output Range
        double m_left = (left_channel_config.max_value - left_channel_config.min_value) / 2.0;
        double m_right = (right_channel_config.max_value - right_channel_config.min_value) / 2.0;

        double b_left = left_channel_config.neutral_value - (m_left * 0.0);
        double b_right = right_channel_config.neutral_value - (m_right * 0.0);

        double left_scaled = left_mixed * m_left + b_left;
        double right_scaled = right_inverted * m_right + b_right;

        // Clip to Min/Max
        double left_clipped = clip(left_scaled, left_channel_config.min_value, left_channel_config.max_value);

        double right_clipped = clip(right_scaled, right_channel_config.min_value, right_channel_config.max_value);

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
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::DriveExecutor