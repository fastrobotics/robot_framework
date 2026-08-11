#include <BasicTrajectoryControllerProcess/BasicTrajectoryControllerProcess.hpp>
#include <Controller/PIDController/PIDController.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
    bool BasicTrajectoryControllerProcess::init() {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::PLANNING);
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        controller_ = new Controller::PIDController;
        Controller::IControllerConfig* config = new Controller::PIDControllerConfig;
        status = controller_->init(config);
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
        return status;
    }
    bool BasicTrajectoryControllerProcess::new_desired_command(fast::rf::messages::GeometryMsgs::TwistMsg cmd) {
        bool status = BaseTrajectoryControllerProcess::new_desired_command(cmd);
        return status;
    }

}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem