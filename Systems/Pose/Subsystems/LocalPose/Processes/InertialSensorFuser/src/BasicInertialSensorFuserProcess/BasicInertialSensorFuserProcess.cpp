#include <BasicInertialSensorFuserProcess/BasicInertialSensorFuserProcess.hpp>
namespace fast::rf::PoseSystem::LocalPoseSubsystem {

    bool BasicInertialSensorFuserProcess::init() {
        bool status = BaseInertialSensorFuser::init();
        if (status == false) {
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        // Add more as needed
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
    bool BasicInertialSensorFuserProcess::update(double current_time_sec) {
        bool status = BaseInertialSensorFuserProcess::update(current_time_sec);
        if (status == false) {
            return false;
        }
        return true;
    }
    std::string BasicInertialSensorFuserProcess::pretty() {
        std::string str = "---Basic InertialSensorFuser Process---";
        str += BaseInertialSensorFuserProcess::pretty();
        return str;
    }

}  // namespace fast::rf::PoseSystem::LocalPoseSubsystem