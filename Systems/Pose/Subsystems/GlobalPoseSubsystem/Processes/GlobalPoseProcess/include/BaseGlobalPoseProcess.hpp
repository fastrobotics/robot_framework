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
  GeometryMsgs::OdomMsg get_GlobalPose() override {
    return global_pose;
  } //!< Get Global Pose
  bool base_update(double current_time_sec,
                   double delta_time_sec); //!< Base function to update

protected:
  double current_time_sec_{-1.0};    //!< Current system time
  GeometryMsgs::OdomMsg global_pose; //!< Computed Global Pose
};
} // namespace fast::rf::PoseSystem::GlobalPoseSubsystem