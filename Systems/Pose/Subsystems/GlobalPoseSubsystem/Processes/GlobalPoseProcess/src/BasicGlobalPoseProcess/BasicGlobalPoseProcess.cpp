#include <BasicGlobalPoseProcess/BasicGlobalPoseProcess.hpp>
namespace fast::rf::PoseSystem::GlobalPoseSubsystem {
bool BasicGlobalPoseProcess::update(double current_time_sec,
                                    double delta_time_sec) {
  bool status = base_update(current_time_sec, delta_time_sec);
  if (status == false) {
    return false;
  }
  return true;
}
bool BasicGlobalPoseProcess::new_GlobalPositionSensorData(
    uint8_t index, SensorMsgs::GlobalPositionSensorData data) {
  return false;
}
} // namespace fast::rf::PoseSystem::GlobalPoseSubsystem