#pragma once
#include <IGlobalPoseProcess.hpp>
namespace fast::rf::PoseSystem::GlobalPoseSubsystem {
/**
 * @brief Base Global Pose Process
  @details Concrete Global Pose Processes should derive from this
 *
 */
class BaseGlobalPoseProcess : public IGlobalPoseProcess {};
} // namespace fast::rf::PoseSystem::GlobalPoseSubsystem