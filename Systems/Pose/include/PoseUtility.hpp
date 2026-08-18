/**
 * @file PoseUtility.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-08-17
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once
#include <AccelMsg.hpp>
#include <OdomMsg.hpp>
namespace fast::rf::PoseSystem {
    /**
     * @brief General Pose Utility content
     *
     */
    class PoseUtility {
       public:
        /**
         * @brief Differentiate 2 Odom Poses
         *
         * @param previous
         * @param current
         * @param computed_angular_acc The computed Angular Acceleration
         * @return true If the data is valid
         * @return false
         */
        static bool differentiate(fast::rf::messages::GeometryMsgs::OdomMsg previous,
                                  fast::rf::messages::GeometryMsgs::OdomMsg current,
                                  fast::rf::messages::GeometryMsgs::AccelMsg& computed_angular_acc);
    };
}  // namespace fast::rf::PoseSystem