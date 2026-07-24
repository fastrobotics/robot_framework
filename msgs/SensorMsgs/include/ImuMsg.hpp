/**
 * @file ImuMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-23
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <Covariance3DMsg.hpp>
#include <OrientationMsg.hpp>
#include <Vector3DMsg.hpp>
#include <string>
#include <vector>

namespace fast::rf::messages::SensorMsgs {
    /**
     * @brief IMUMsg Data
     *
     */
    struct ImuMsg {
        double time_stamp;                                                              //!< Timestamp of data
        uint64_t seq;                                                                   //!< Sequence Number
        fast::rf::messages::GeometryMsgs::OrientationMsg orientation;                   //!< Euler Angle Orientation
        fast::rf::messages::StandardMsgs::Covariance3DMsg orientation_covariance;       //!< Orientation Covariance
        fast::rf::messages::StandardMsgs::Vector3DMsg angular_velocity;                 //!< Angular Velocity
        fast::rf::messages::StandardMsgs::Covariance3DMsg angular_velocity_covariance;  //!< Angular Velocity Covariance
        fast::rf::messages::StandardMsgs::Vector3DMsg linear_acceleration;              //!< Linear Acceleration
        fast::rf::messages::StandardMsgs::Covariance3DMsg
            linear_acceleration_covariance;  //!< Linear Acceleration Covariance
        ImuMsg() : time_stamp(-1.0) {}

        /**
         * @brief Human readable string of the data
         *
         * @return std::string
         */
        std::string pretty() {
            std::string str = "T: " + std::to_string(time_stamp) + " S: " + std::to_string(seq) + "\n";
            str += "Orientation:\n";
            str += "\t" + orientation.pretty() + "\n";
            str += "Angular Velocity:\n";
            str += "\t" + angular_velocity.pretty() + "\n";
            str += "Linear Acceleration:\n";
            str += "\t" + linear_acceleration.pretty() + "\n";
            return str;
        }
    };
}  // namespace fast::rf::messages::SensorMsgs
