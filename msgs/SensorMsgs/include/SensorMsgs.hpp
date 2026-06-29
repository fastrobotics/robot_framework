/**
 * @file SensorMsgs.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <StandardMsgs.hpp>
#include <cstdint>

using namespace fast::rf::messages::StandardMsgs;
/**
 * @brief Messages for Sensors
 *
 */
namespace fast::rf::messages::SensorMsgs {
/**
 * @brief Data Structure for encoding GPS Data
 *
 */
struct GlobalPositionSensorMsg {
    double time_stamp;                                 //!< Timestamp of data
    double latitude_deg;                               //!< Latitude in Degrees.  Range is [-90.0,90.0]
    double longitude_deg;                              //!< Longitude in Degrees.  Range is [-90.0, 90.0]
    double altitude_m;                                 //!< Altitude above sea level
    uint16_t satellites;                               //!< Number of satellites used for data
    Covariance3DMsg covariance;                        //!< Covariance of Global Position Data
    static inline constexpr double MAX_ANGLE = 90.0;   //!< Max Angle in degrees representing Geographic Coordinates
    static inline constexpr double MIN_ANGLE = -90.0;  //!< Min Angle in degrees representing Geographic Coordinates
    static inline constexpr uint16_t COV_X = Covariance3DMsg::X1;  //!< Covariance Index representing X Position.
    static inline constexpr uint16_t COV_Y = Covariance3DMsg::X2;  //!< Covariance Index representing Y Position.
    static inline constexpr uint16_t COV_Z = Covariance3DMsg::X3;  //!< Covariance Index representing Z Position.
    GlobalPositionSensorMsg() {};
    /**
     * @brief Checks data to see if valid
     *
     * @return true Data is valid
     * @return false Data is not valid
     */
    bool ok() {
        if (latitude_deg > MAX_ANGLE) {
            return false;
        }
        if (latitude_deg < MIN_ANGLE) {
            return false;
        }
        if (longitude_deg > MAX_ANGLE) {
            return false;
        }
        if (longitude_deg < MIN_ANGLE) {
            return false;
        }
        return true;
    }
};
}  // namespace fast::rf::messages::SensorMsgs
