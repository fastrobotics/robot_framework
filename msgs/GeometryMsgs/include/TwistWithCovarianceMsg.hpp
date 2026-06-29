
/**
 * @file TwistWithCovarianceMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-24
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <Covariance6DMsg.hpp>
#include <TwistMsg.hpp>
#include <string>
#include <vector>
using namespace fast::rf::messages::StandardMsgs;
/**
 * @brief Geometry Messages Namespace
 *
 */
namespace fast::rf::messages::GeometryMsgs {

/**
 * @brief Data Structure for encoding Velocity and Covariance
 *
 */
struct TwistWithCovarianceMsg {
    static inline constexpr uint16_t COV_LINEAR_X =
        Covariance6DMsg::X1;  //!< Covariance Index representing X Linear Velocity.
    static inline constexpr uint16_t COV_LINEAR_Y =
        Covariance6DMsg::X2;  //!< Covariance Index representing Y Linear Velocity.
    static inline constexpr uint16_t COV_LINEAR_Z =
        Covariance6DMsg::X3;  //!< Covariance Index representing Z Linear Velocity.
    static inline constexpr uint16_t COV_ANGULAR_ROLL = Covariance6DMsg::X4;   //!< Covariance Index representing Roll
                                                                               //!< Angular Velocity.
    static inline constexpr uint16_t COV_ANGULAR_PITCH = Covariance6DMsg::X5;  //!< Covariance Index representing Pitch
                                                                               //!< Angular Velocity.
    static inline constexpr uint16_t COV_ANGULAR_YAW =
        Covariance6DMsg::X6;     //!< Covariance representing Yaw Angular Velocity.
    TwistMsg twist;              //!< 6D Velocity
    Covariance6DMsg covariance;  //!< Error estimate of velocity.  Diagonal
                                 //!< elements representing the following: >0: Real
                                 //!< values; =0: Unsupported; <0: Unknown
    TwistWithCovarianceMsg() {};
};
}  // namespace fast::rf::messages::GeometryMsgs