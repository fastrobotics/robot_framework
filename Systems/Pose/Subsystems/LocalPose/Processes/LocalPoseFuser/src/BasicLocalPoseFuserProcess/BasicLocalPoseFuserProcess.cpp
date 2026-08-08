#include <BasicLocalPoseFuserProcess/BasicLocalPoseFuserProcess.hpp>
namespace fast::rf::PoseSystem::LocalPoseSubsystem {

bool BasicLocalPoseFuserProcess::init() {
  bool status = BaseLocalPoseFuser::init();
  if(status == false) {
    return false;
  }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        // Add more as needed
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
bool BasicLocalPoseFuserProcess::update(double current_time_sec) {
  bool status = BaseLocalPoseFuserProcess::update(current_time_sec);
  if (status == false) {
    return false;
  }
  return true;
}
std::string BasicLocalPoseFuserProcess::pretty() {
    std::string str = "---Basic LocalPoseFuser Process---";
    str += BaseLocalPoseFuserProcess::pretty();
    return str;
}

} // namespace fast::rf::PoseSystem::LocalPoseSubsystem