#include <BasicGlobalPoseProcess/BasicGlobalPoseProcess.hpp>
#include <GeographicLib/UTMUPS.hpp>
#include <string>
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
  int zone;
  bool northp;
  double x, y;
  GeographicLib::UTMUPS::Forward(data.latitude_deg, data.longitude_deg, zone,
                                 northp, x, y);
  std::string zonestr = GeographicLib::UTMUPS::EncodeZone(zone, northp);
  global_pose.pose.pose.position.x = x;
  global_pose.pose.pose.position.y = y;
  return false;
}
} // namespace fast::rf::PoseSystem::GlobalPoseSubsystem