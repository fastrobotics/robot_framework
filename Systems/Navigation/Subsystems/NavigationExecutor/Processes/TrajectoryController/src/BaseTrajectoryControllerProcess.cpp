/**
 * @compare_tag Process-BaseSource v0.1
 *
 */
#include <BaseTrajectoryControllerProcess.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectoryController {
    bool BaseTrajectoryControllerProcess::init() {
        if (controller_ == nullptr) {
            return false;
        }
        return true;
    }
    bool BaseTrajectoryControllerProcess::get_command(fast::rf::messages::GeometryMsgs::TwistMsg& cmd) {
        bool new_command = is_new_command;
        cmd = command_;
        is_new_command = false;
        return new_command;
    }
    void BaseTrajectoryControllerProcess::set_command(fast::rf::messages::GeometryMsgs::TwistMsg command) {
        m_diagnosticManager.updateDiagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::NOERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Command Output Computed.");
        command_ = command;
        is_new_command = true;
    }
    bool BaseTrajectoryControllerProcess::new_pose([[maybe_unused]] fast::rf::messages::GeometryMsgs::OdomMsg pose) {
        return true;
    }
    bool BaseTrajectoryControllerProcess::new_desired_command(fast::rf::messages::GeometryMsgs::TwistMsg cmd) {
        latest_desired_command = cmd;
        return true;
    }
    std::string BaseTrajectoryControllerProcess::pretty() {
        std::string str = "---Base Trajectory Controller Proess---\n";
        str += "\tSys: " + std::string(fast::rf::NavigationSystem::toString(fast::rf::NavigationSystem::Id{})) + "/" +
               std::string(fast::rf::NavigationSystem::NavigationExecutorSubsystem::toString(
                   fast::rf::NavigationSystem::NavigationExecutorSubsystem::Id{})) +
               "/" +
               std::string(fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectoryController::toString(
                   fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectoryController::Id{})) +
               "\n";
        str += "\tT: " + std::to_string(m_currentTimeSec) + "\n";
        str += m_diagnosticManager.pretty();
        str += "Command:\n";
        str += "\tIs New: " + std::to_string(is_new_command) + "\n";
        str += "\t" + command_.pretty();
        return str;
    }
    bool BaseTrajectoryControllerProcess::update(double currentTimeSec) {
        m_currentTimeSec = currentTimeSec;
        if (controller_ == nullptr) {
            return false;
        }
        bool status = controller_->update(m_currentTimeSec);
        if (m_diagnosticManager.getDiagnostics(fast::rf::Level::WARN).size() == 0) {
            ready_to_arm.ready_to_arm = true;
        } else {
            ready_to_arm.ready_to_arm = false;
        }
        return status;
    }
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectoryController
