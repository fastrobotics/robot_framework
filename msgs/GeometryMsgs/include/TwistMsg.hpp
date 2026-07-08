/**
 * @file TwistMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-24
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <Vector3DMsg.hpp>
#include <string>
#include <vector>
using namespace fast::rf::messages::StandardMsgs;
namespace fast::rf::messages::GeometryMsgs {

    /**
     * @brief Data Structure for encoding Velocity (linear and angular)
     *
     */
    struct TwistMsg {
        Vector3DMsg linear;   //!< Linear Velocity
        Vector3DMsg angular;  //!< Angular velocity
        TwistMsg(){};

        /**
         * @brief Print a human readable version of the data
         *
         * @return std::string
         */
        std::string pretty() {
            std::string str = "Lin: " + linear.pretty() + " Ang: " + angular.pretty();
            return str;
        }
    };
}  // namespace fast::rf::messages::GeometryMsgs