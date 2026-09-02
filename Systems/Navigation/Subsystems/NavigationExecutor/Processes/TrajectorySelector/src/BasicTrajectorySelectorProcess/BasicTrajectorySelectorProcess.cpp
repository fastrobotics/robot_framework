/**
 * @compare_tag Process-BasicSource v0.1
 *
 */
#include <BasicTrajectorySelectorProcess/BasicTrajectorySelectorProcess.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectorySelector {
    bool BasicTrajectorySelectorProcess::init() {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        // Add others as needed
        bool status = m_diagnosticManager.initializeDiagnostics(diagnostic_types);
        return status;
    }
    bool BasicTrajectorySelectorProcess::update(double currentTimeSec) {
        bool status = BaseTrajectorySelectorProcess::update(currentTimeSec);
        if (status == false) {
            return false;
        }
        return true;
    }
    std::string BasicTrajectorySelectorProcess::pretty() {
        std::string str = "---Basic Trajectory Selector Process---";
        str += BaseTrajectorySelectorProcess::pretty();
        return str;
    }

}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectorySelector
