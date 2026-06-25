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
   * @brief Provide a GPS Position Sensor Input
   *
   * @param index The index of the channel
   * @param data The GPS Data
   * @return true If the data was processed ok
   * @return false If the data was not processed ok
   */
  virtual bool
  new_GlobalPositionSensorData(uint8_t index,
                               SensorMsgs::GlobalPositionSensorData data) = 0;
};
} // namespace fast::rf::PoseSystem::GlobalPoseSubsystem