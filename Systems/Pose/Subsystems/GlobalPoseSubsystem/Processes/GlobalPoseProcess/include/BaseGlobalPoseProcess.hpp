/**
 * @file BaseGlobalPoseProcess.hpp
 * @author yDavid Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <IGlobalPoseProcess.hpp>
namespace fast::rf::PoseSystem::GlobalPoseSubsystem {
/**
 * @brief Base Global Pose Process
  @details Concrete Global Pose Processes should derive from this
 *
 */
class BaseGlobalPoseProcess : public IGlobalPoseProcess {
   public:
    /**
     * @brief Construct a new Base Global Pose Process object
     *
     * @param supported_gps_channels
     */
    BaseGlobalPoseProcess(uint8_t supported_gps_channels) : supported_gps_channels(supported_gps_channels) {}
    /**
     * @brief Get the supported gps channel count object
     *
     * @return uint8_t The number of supported gps channels
     */
    uint8_t get_supported_gps_channel_count() { return supported_gps_channels; }
    /**
     * @brief Get the GlobalPose object
     *
     * @return GeometryMsgs::OdomMsg
     */
    GeometryMsgs::OdomMsg get_GlobalPose() override { return global_pose; }  //!< Get Global Pose
    /**
     * @brief Update the base object
     *
     * @param current_time_sec
     * @param delta_time_sec
     * @return true If ok
     * @return false If not ok
     */
    bool base_update(double current_time_sec,
                     double delta_time_sec);  //!< Base function to update

   protected:
    double current_time_sec_{-1.0};     //!< Current system time
    GeometryMsgs::OdomMsg global_pose;  //!< Computed Global Pose
    uint8_t supported_gps_channels{0};  //!< Number of supported GPS Channels
};
}  // namespace fast::rf::PoseSystem::GlobalPoseSubsystem