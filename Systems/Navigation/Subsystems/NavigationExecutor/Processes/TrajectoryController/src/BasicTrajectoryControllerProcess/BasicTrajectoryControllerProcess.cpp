#include <BasicTrajectoryControllerProcess/BasicTrajectoryControllerProcess.hpp>

namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
    bool BasicTrajectoryControllerProcess::init() {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::PLANNING);
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        controller_ = new Controller::PIDController;
        controller_->init();
        status = set_parameters(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
        return status;
    }
    bool BasicTrajectoryControllerProcess::set_parameters(double max_output, double min_output,
                                                          double sensor_scale_factor, double K_P, double K_I,
                                                          double K_D) {
        Controller::PIDControllerConfig config;
        config.set_parameters(max_output, min_output, K_P, K_I, K_D, sensor_scale_factor);

        auto* controller = dynamic_cast<Controller::PIDController*>(controller_);
        bool status = controller->set_config(config);

        printf("xxx1\n");
        fast::rf::Logger::log_debug(pretty());
        return status;
    }
    bool BasicTrajectoryControllerProcess::update(double current_time_sec) {
        bool status = BaseTrajectoryControllerProcess::update(current_time_sec);
        if (status == false) {
            return false;
        }

        return true;
    }
    std::string BasicTrajectoryControllerProcess::pretty() {
        std::string str = "---Basic Trajectory Controller Process---\n";

        str += BaseTrajectoryControllerProcess::pretty();

        auto* controller = dynamic_cast<Controller::PIDController*>(controller_);

        str += controller->pretty();

        return str;
    }
    bool BasicTrajectoryControllerProcess::new_pose(fast::rf::messages::GeometryMsgs::OdomMsg pose) {
        bool status = BaseTrajectoryControllerProcess::new_pose(pose);
        if (status == false) {
            return false;
        }
        status = controller_->new_sensor_input(pose.twist.twist.angular.z, current_time_sec_);
        auto cmd = latest_desired_command;
        auto controller_output_ = controller_->get_output();
        cmd.angular.z = controller_output_->command_value;
        set_command(cmd);
        return controller_output_->is_new;
    }
    bool BasicTrajectoryControllerProcess::new_desired_command(fast::rf::messages::GeometryMsgs::TwistMsg cmd) {
        bool status = BaseTrajectoryControllerProcess::new_desired_command(cmd);
        if (status == false) {
            return false;
        }
        status = controller_->new_set_point(cmd.angular.z, current_time_sec_);
        return status;
    }

}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem