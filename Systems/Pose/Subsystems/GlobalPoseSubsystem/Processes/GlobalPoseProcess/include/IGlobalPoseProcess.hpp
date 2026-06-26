#pragma once
#include <GeometryMsgs.hpp>
#include <SensorMsgs.hpp>
using namespace fast::rf::messages;
namespace fast::rf::PoseSystem::GlobalPoseSubsystem {
/**
 * @brief Interface for the Global Pose Process
 *
 */
class IGlobalPoseProcess {
public:
  IGlobalPoseProcess() = default;
  virtual ~IGlobalPoseProcess() = default;
  /**
   * @brief Get the supported gps channel count object
   *
   * @return uint8_t Number of Channels Supported
   */
  virtual uint8_t get_supported_gps_channel_count() = 0;
  /**
   * @brief Generic Update function
   *
   * @param current_time_sec Current time stamp
   * @param delta_time_sec Difference in time between previous iterations
   * @return true If the process updated ok
   * @return false If the process did not update ok
   */
  virtual bool update(double current_time_sec, double delta_time_sec) = 0;
  /**
   * @brief Provide a GPS Position Sensor Input
   *
   * @param index The index of the channel
   * @param data The GPS Data
   * @return true If the data was processed ok
   * @return false If the data was not processed ok
   */
  virtual bool
  new_GlobalPositionSensorMsg(uint8_t index,
                              SensorMsgs::GlobalPositionSensorMsg data) = 0;
  /**
   * @brief Get the GlobalPose object
   *
   * @return GeometryMsgs::OdomMsg
   */
  virtual GeometryMsgs::OdomMsg get_GlobalPose() = 0;
};
} // namespace fast::rf::PoseSystem::GlobalPoseSubsystem