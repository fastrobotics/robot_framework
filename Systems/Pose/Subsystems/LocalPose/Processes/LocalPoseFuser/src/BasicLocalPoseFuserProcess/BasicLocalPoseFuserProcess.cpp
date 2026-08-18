#include <BasicLocalPoseFuserProcess/BasicLocalPoseFuserProcess.hpp>
#include <PoseUtility.hpp>
#include <cmath>
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
        double prev_time = current_time_sec_;

        bool status = BaseLocalPoseFuserProcess::update(current_time_sec);
        if (prev_time > 0.0) {
            double delta_t = (current_time_sec - prev_time);
            normal_rotate_accel_timer += delta_t;
        }
        if (normal_rotate_accel_timer > 5.0) {
            excessive_rotate_accel = false;
        }
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
        bool any_error = false;
        diagnosticManager.update_diagnostic(
            fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::NOERROR,
            fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Receiving Machine Inertial Data");
        auto prev_local_pose = local_pose;
        // Compute Local Pose

        local_pose.time_stamp = machine_inertial_data.time_stamp;
        local_pose.twist.twist.angular = machine_inertial_data.angular_velocity;

        // Fill in Twist Covariance during AB#1813

        fast::rf::messages::GeometryMsgs::AccelWithCovarianceMsg angular_acc_covariance;
        // Compute Angular Acceleration
        fast::rf::messages::GeometryMsgs::AccelMsg angular_acc;
        bool status = PoseUtility::differentiate(prev_local_pose, local_pose, angular_acc);
        if (status == false) {
            any_error = true;
            diagnosticManager.update_diagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE,
                                                fast::rf::Level::WARN,
                                                fast::rf::DiagnosticDefinition::DiagnosticMessage::DIAGNOSTIC_FAILED,
                                                "Not able to differentiate Local Pose!");
        }
        angular_acc_covariance.accel = angular_acc;
        if ((std::fabs(angular_acc.angular.x) > HIGH_ANGULARRATE_DISARM_LIMIT) ||
            (std::fabs(angular_acc.angular.y) > HIGH_ANGULARRATE_DISARM_LIMIT) ||
            (std::fabs(angular_acc.angular.z) > HIGH_ANGULARRATE_DISARM_LIMIT)) {
            excessive_rotate_accel = true;
            normal_rotate_accel_timer = 0.0;
        }
        if (excessive_rotate_accel == true) {
            any_error = true;
            diagnosticManager.update_diagnostic(fast::rf::DiagnosticDefinition::DiagnosticType::POSE,
                                                fast::rf::Level::ERROR,
                                                fast::rf::DiagnosticDefinition::DiagnosticMessage::DIAGNOSTIC_FAILED,
                                                "High Angular Acceleration: " + angular_acc.angular.pretty() + " > " +
                                                    std::to_string(HIGH_ANGULARRATE_DISARM_LIMIT) + "  Disarming!");
        }
        angular_acc_covariance.time_stamp = local_pose.time_stamp;

        // Fill in Angular Acc Covariance during AB#1813

        if (any_error == false) {
            diagnosticManager.update_diagnostic(
                fast::rf::DiagnosticDefinition::DiagnosticType::POSE, fast::rf::Level::NOERROR,
                fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Local Pose Updated");
        }

        new_local_pose(local_pose, angular_acc_covariance);

        return true;
    }

}  // namespace fast::rf::PoseSystem::LocalPoseSubsystem