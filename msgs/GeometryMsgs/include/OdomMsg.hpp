/**
 * @file OdomMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-24
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <PoseWithCovarianceMsg.hpp>
#include <TwistWithCovarianceMsg.hpp>
#include <string>
#include <vector>
namespace fast::rf::messages::GeometryMsgs {


  
/**
 * @brief Data structure for encoding Odometry
 *
 */
struct OdomMsg {
    double time_stamp;             //!< Timestamp of reported odometry
    PoseWithCovarianceMsg pose;    //!< Pose and Error Estimate
    TwistWithCovarianceMsg twist;  //!< Velocity and Error Estimate
    OdomMsg()
        : time_stamp(-1.0) {

          };
    /**
     * @brief Human readable function to print data
     *
     * @return std::string
     */
    std::string pretty() {
        std::string str = "";
        str = "T: " + std::to_string(time_stamp) + " X: " + std::to_string(pose.pose.position.x) +
              " Y: " + std::to_string(pose.pose.position.y);
        return str;
    }
};
}  // namespace fast::rf::messages::GeometryMsgs