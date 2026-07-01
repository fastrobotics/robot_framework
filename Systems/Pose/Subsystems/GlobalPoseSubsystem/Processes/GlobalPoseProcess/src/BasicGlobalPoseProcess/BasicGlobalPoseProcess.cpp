#include <BasicGlobalPoseProcess/BasicGlobalPoseProcess.hpp>
#include <GeographicLib/UTMUPS.hpp>
#include <string>
namespace fast::rf::PoseSystem::GlobalPoseSubsystem {
bool BasicGlobalPoseProcess::update(double current_time_sec, [[maybe_unused]] double delta_time_sec) {
    bool status = base_update(current_time_sec, delta_time_sec);
    if (status == false) {
        return false;
    }
    return true;
}
bool BasicGlobalPoseProcess::new_GlobalPositionSensorMsg(uint8_t index, SensorMsgs::GlobalPositionSensorMsg gps_data) {
    if (index >= supported_gps_channels) {
        return false;
    }
    if (gps_data.time_stamp <= 0.0) {
        return false;
    }
    int zone;
    bool northp;
    double x, y;
    GeographicLib::UTMUPS::Forward(gps_data.latitude_deg, gps_data.longitude_deg, zone, northp, x, y);
    std::string zonestr = GeographicLib::UTMUPS::EncodeZone(zone, northp);
    global_pose.time_stamp = gps_data.time_stamp;
    global_pose.pose.pose.position.x = x;
    global_pose.pose.pose.position.y = y;
    global_pose.pose.pose.position.z = gps_data.altitude_m;
    global_pose.pose.covariance.covariance[GeometryMsgs::PoseWithCovarianceMsg::COV_X] =
        gps_data.covariance.covariance[SensorMsgs::GlobalPositionSensorMsg::COV_X];

    global_pose.pose.covariance.covariance[GeometryMsgs::PoseWithCovarianceMsg::COV_Y] =
        gps_data.covariance.covariance[SensorMsgs::GlobalPositionSensorMsg::COV_Y];

    global_pose.pose.covariance.covariance[GeometryMsgs::PoseWithCovarianceMsg::COV_Z] =
        gps_data.covariance.covariance[SensorMsgs::GlobalPositionSensorMsg::COV_Z];
    return true;
}
}  // namespace fast::rf::PoseSystem::GlobalPoseSubsystem