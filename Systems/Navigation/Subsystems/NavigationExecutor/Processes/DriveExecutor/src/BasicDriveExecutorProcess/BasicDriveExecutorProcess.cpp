/**
 * @compare_tag Process-BasicSource v0.1
 *
 */
#include <BasicDriveExecutorProcess/BasicDriveExecutorProcess.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::DriveExecutor {
    bool BasicDriveExecutorProcess::init() {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::REMOTE_CONTROL);
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::ACTUATORS);
        bool status = diagnosticManager.initializeDiagnostics(diagnostic_types);
        return status;
    }

    IDriveExecutorOutput* BasicDriveExecutorProcess::new_cmd([[maybe_unused]] GeometryMsgs::TwistMsg cmd) {
        IDriveExecutorOutput* output = nullptr;
        return output;
    }
    bool BasicDriveExecutorProcess::update(double current_time_sec) {
        bool status = BaseDriveExecutorProcess::update(current_time_sec);
        // GCOV_EXCL_START
        // This will always be ok
        if (status == false) {
            return false;
        }
        // GCOV_EXCL_STOP
        return true;
    }
    std::string BasicDriveExecutorProcess::pretty() {
        std::string str = "---Basic Drive Executor Process---";
        str += BaseDriveExecutorProcess::pretty();
        return str;
    }

}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::DriveExecutor
