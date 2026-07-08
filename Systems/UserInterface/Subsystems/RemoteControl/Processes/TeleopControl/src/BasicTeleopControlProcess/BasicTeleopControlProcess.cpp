#include <BasicTeleopControlProcess/BasicTeleopControlProcess.hpp>
namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem {
    bool BasicTeleopControlProcess::set_config(double forward_velocity_x_step_change,
                                               double angular_velocity_z_step_change, double max_forward_x_velocity,
                                               double max_reverse_x_velocity, double max_angular_z_velocity,
                                               double min_angular_z_velocity) {
        // Forward Velocity Checks
        if (max_forward_x_velocity < max_reverse_x_velocity) {
            return false;
        }
        double delta_forward_velocity = max_forward_x_velocity - max_reverse_x_velocity;
        if (forward_velocity_x_step_change > delta_forward_velocity) {
            return false;
        }
        // Angular Velocity Checks
        if (max_angular_z_velocity < min_angular_z_velocity) {
            return false;
        }
        double delta_rotation_velocity = max_angular_z_velocity - min_angular_z_velocity;
        if (angular_velocity_z_step_change > delta_rotation_velocity) {
            return false;
        }
        forward_velocity_x_step_change_ = forward_velocity_x_step_change;
        angular_velocity_z_step_change_ = angular_velocity_z_step_change;
        max_forward_x_velocity_ = max_forward_x_velocity;
        max_reverse_x_velocity_ = max_reverse_x_velocity;
        max_angular_z_velocity_ = max_angular_z_velocity;
        min_angular_z_velocity_ = min_angular_z_velocity;
        return true;
    }
    bool BasicTeleopControlProcess::init() {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::REMOTE_CONTROL);
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
    bool BasicTeleopControlProcess::update([[maybe_unused]] double current_time_sec,
                                           [[maybe_unused]] double delta_time_sec) {
        bool status = BaseTeleopControlProcess::base_update(current_time_sec, delta_time_sec);
        if (status == false) {
            return false;
        }
        return true;
    }
    bool BasicTeleopControlProcess::key_pressed(KeyPressed key) {
        auto current_desired_twist = desired_twist;
        bool changed = false;
        switch (key) {
            case KeyPressed::SPACE_BAR:  //!< Command a Stop
                if (operation_mode == OperationMode::KEY_TEST) {
                    printf("KEY: SPACE BAR\n");
                } else if (operation_mode == OperationMode::RUN) {
                    current_desired_twist.linear.x = 0.0;
                    current_desired_twist.linear.y = 0.0;
                    current_desired_twist.linear.z = 0.0;
                    current_desired_twist.angular.x = 0.0;
                    current_desired_twist.angular.y = 0.0;
                    current_desired_twist.angular.z = 0.0;
                    changed = true;
                }
                break;

            case KeyPressed::UP_ARROW:  //!< Increase Forward Velocity
                if (operation_mode == OperationMode::KEY_TEST) {
                    printf("KEY: UP ARROW\n");
                } else if (operation_mode == OperationMode::RUN) {
                    current_desired_twist.linear.x += forward_velocity_x_step_change_;
                    if (current_desired_twist.linear.x <= max_forward_x_velocity_) {
                        changed = true;
                    }
                }
                break;
            case KeyPressed::DOWN_ARROW:  //!< Decrease Forward Velocity
                if (operation_mode == OperationMode::KEY_TEST) {
                    printf("KEY: DOWN ARROW\n");
                } else if (operation_mode == OperationMode::RUN) {
                    current_desired_twist.linear.x -= forward_velocity_x_step_change_;
                    if (current_desired_twist.linear.x >= (max_reverse_x_velocity_)) {
                        changed = true;
                    }
                }
                break;
            case KeyPressed::LEFT_ARROW:  //!< Increase Left Turn Velocity
                if (operation_mode == OperationMode::KEY_TEST) {
                    printf("KEY: LEFT ARROW\n");
                } else if (operation_mode == OperationMode::RUN) {
                    current_desired_twist.angular.z += angular_velocity_z_step_change_;
                    if (current_desired_twist.angular.z <= max_angular_z_velocity_) {
                        changed = true;
                    }
                }
                break;
            case KeyPressed::RIGHT_ARROW:  //!< Increase Right Turn Velocity
                if (operation_mode == OperationMode::KEY_TEST) {
                    printf("KEY: RIGHT ARROW\n");
                } else if (operation_mode == OperationMode::RUN) {
                    current_desired_twist.angular.z -= angular_velocity_z_step_change_;
                    if (current_desired_twist.angular.z >= (min_angular_z_velocity_)) {
                        changed = true;
                    }
                }
                break;
            default:
                return false;
        }

        if (changed) {
            desired_twist = current_desired_twist;
        }
        return true;
    }

}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem