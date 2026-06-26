#pragma once

#include <BaseGlobalPoseProcess.hpp>
namespace fast::rf::PoseSystem::GlobalPoseSubsystem {
/**
 * @brief Minimal implementation for a Global Pose Process
 *
 */
class BasicGlobalPoseProcess : public BaseGlobalPoseProcess {
public:
  /**
   * @brief Update with recent timing data
   *
   * @param current_time_sec
   * @param delta_time_sec
   * @return true If update executed ok
   * @return false If update executed with some error
   */
  bool update(double current_time_sec, double delta_time_sec) override;
  /**
   * @brief Process a GPS Position Sensor Data
   *
   * @param index The index of the GPS Sensor
   * @param data The GPS Data
   * @return true If the data was processed ok
   * @return false If the data did not process ok
   */
  bool new_GlobalPositionSensorData(
      uint8_t index, SensorMsgs::GlobalPositionSensorData data) override;
};
} // namespace fast::rf::PoseSystem::GlobalPoseSubsystem