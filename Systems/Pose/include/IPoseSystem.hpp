/**
 * @file IPoseSystem.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-24
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <GeometryMsgs.hpp>

namespace fast::rf::PoseSystem {
/**
 * @brief Interface for the Pose System
 *
 */
class IPoseSystem {
   public:
    IPoseSystem() = default;
    virtual ~IPoseSystem() = default;
    /**
     * @brief
     *
     * @param current_time_sec
     * @param delta_time_sec
     * @return true
     * @return false
     */
    virtual bool update(double current_time_sec, double delta_time_sec) = 0;
    /**
     * @brief Get the global pose object
     *
     * @return fast::rf::messages::GeometryMsgs::OdomMsg
     */
    virtual fast::rf::messages::GeometryMsgs::OdomMsg get_global_pose() = 0;
    /**
     * @brief Get the local pose object
     *
     * @return fast::rf::messages::GeometryMsgs::OdomMsg
     */
    virtual fast::rf::messages::GeometryMsgs::OdomMsg get_local_pose() = 0;
};
}  // namespace fast::rf::PoseSystem