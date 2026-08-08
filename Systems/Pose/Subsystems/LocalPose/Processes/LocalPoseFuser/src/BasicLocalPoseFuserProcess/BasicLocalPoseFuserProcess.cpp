#include <BasicLocalPoseFuserProcess/BasicLocalPoseFuserProcess.hpp>
namespace fast::rf::PoseSystem::LocalPoseSubsystem {

    bool BasicLocalPoseFuserProcess::init() {
        bool status = BaseLocalPoseFuserProcess::init();
        // GCOV_EXCL_START
        // No practical need for this
        if (status == false) {
            return false;
        }
        // GCOV_EXCL_STOP
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::POSE);

        status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        diagnosticManager.update_diagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::POSE, fast::rf::Level::WARN,
                                            fast::rf::DiagnosticDefinition::DiagnosticMessage::DIAGNOSTIC_FAILED,
                                            "No Valid Pose Yet.");
        return status;
    }
    bool BasicLocalPoseFuserProcess::update(double current_time_sec) {
        bool status = BaseLocalPoseFuserProcess::update(current_time_sec);
        // GCOV_EXCL_START
        // No practical need for this
        if (status == false) {
            return false;
        }
        // GCOV_EXCL_STOP
        return true;
    }
    std::string BasicLocalPoseFuserProcess::pretty() {
        std::string str = "---Basic LocalPoseFuser Process---";
        str += BaseLocalPoseFuserProcess::pretty();
        return str;
    }
    bool BasicLocalPoseFuserProcess::new_machine_inertial_data(
        fast::rf::messages::SensorMsgs::ImuMsg machine_inertial_data) {
        diagnosticManager.update_diagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::NOERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Receiving Machine Inertial Data");

        fast::rf::messages::GeometryMsgs::OdomMsg local_pose;
        // Compute Local Pose
        local_pose.time_stamp = machine_inertial_data.time_stamp;
        local_pose.twist.twist.angular = machine_inertial_data.angular_velocity;

        // Fill in Twist Covariance during AB#1813

        diagnosticManager.update_diagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::POSE, fast::rf::Level::NOERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Local Pose Updated");

        new_local_pose(local_pose);

        return true;
    }

}  // namespace fast::rf::PoseSystem::LocalPoseSubsystem