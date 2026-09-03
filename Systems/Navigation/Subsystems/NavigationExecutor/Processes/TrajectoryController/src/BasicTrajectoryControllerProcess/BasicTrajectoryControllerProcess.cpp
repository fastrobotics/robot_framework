/**
 * @compare_tag Process-BasicSource v0.1
 *
 */
#include <BasicTrajectoryControllerProcess/BasicTrajectoryControllerProcess.hpp>

namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectoryController {
    bool BasicTrajectoryControllerProcess::init() {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::POSE);
        bool status = m_diagnosticManager.initializeDiagnostics(diagnostic_types);
        m_diagnosticManager.updateDiagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::POSE, fast::rf::Level::WARN,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::DEVICE_NOT_AVAILABLE, "No Pose Update Yet");
        m_diagnosticManager.updateDiagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::WARN,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::DEVICE_NOT_AVAILABLE, "No Ouput Data Computed Yet.");
        controller_ = new Controller::PIDController;
        controller_->init();
        return status;
    }
    bool BasicTrajectoryControllerProcess::set_config(BasicTrajectoryControllerConfig config) {
        if (config.is_ok() == false) {
            return false;
        }
        auto* controller = dynamic_cast<Controller::PIDController*>(controller_);
        bool status = controller->set_config(config.get_pid_controller_config());
        config_ = config;
        return status;
    }
    bool BasicTrajectoryControllerProcess::update(double currentTimeSec) {
        bool status = BaseTrajectoryControllerProcess::update(currentTimeSec);
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
        m_diagnosticManager.updateDiagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::POSE, fast::rf::Level::NOERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Pose Received");
        status = controller_->new_sensor_input(pose.twist.twist.angular.z, m_currentTimeSec);
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
        status = controller_->new_set_point(cmd.angular.z, m_currentTimeSec);
        return status;
    }

}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectoryController
