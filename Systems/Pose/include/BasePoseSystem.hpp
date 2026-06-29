/**
 * @file BasePoseSystem.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-24
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <IPoseSystem.hpp>
#include <OdomMsg.hpp>

namespace fast::rf::PoseSystem {
/**
 * @brief Base Class for the Pose System
 *
 */
class BasePoseSystem : public IPoseSystem {
   public:
    /**
     * @brief Get the global pose object
     *
     * @return fast::rf::messages::GeometryMsgs::OdomMsg
     */
    fast::rf::messages::GeometryMsgs::OdomMsg get_global_pose() override { return global_pose_; }
    /**
     * @brief Get the local pose object
     *
     * @return fast::rf::messages::GeometryMsgs::OdomMsg
     */
    fast::rf::messages::GeometryMsgs::OdomMsg get_local_pose() override { return local_pose_; }

   protected:
    /**
     * @brief
     *
     * @param current_time_sec
     * @param delta_time_sec
     * @return true
     * @return false
     */
    bool base_update(double current_time_sec, double delta_time_sec);

    double current_time_sec_{-1.0};                          //!< Current Time of System
    fast::rf::messages::GeometryMsgs::OdomMsg global_pose_;  //!< Computed Global Pose
    fast::rf::messages::GeometryMsgs::OdomMsg local_pose_;   //!< Computed Local Pose
};
}  // namespace fast::rf::PoseSystem