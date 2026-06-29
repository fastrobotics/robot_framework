#include <BasicDriveExecutorProcess/BasicDriveExecutorProcess.hpp>
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
IDriveExecutorOutput *
BasicDriveExecutorProcess::new_cmd(GeometryMsgs::TwistMsg cmd) {
  IDriveExecutorOutput *output = nullptr;
  return output;
}
bool BasicDriveExecutorProcess::update(double current_time_sec,
                                       double delta_time_sec) {
  bool status =
      BaseDriveExecutorProcess::base_update(current_time_sec, delta_time_sec);
  if (status == false) {
    return false;
  }
  return true;
}

} // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem