/**
 * @file MagneticFieldMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <Covariance3DMsg.hpp>
#include <Vector3DMsg.hpp>
#include <string>
namespace fast::rf::messages::SensorMsgs {
    /**
     * @brief MagneticField Data
     * @details Covariance special Values:
     * Variance(Diagonal) -> 0: Unknown, -> -1: Not supported, do not use measurement
     * Covariance -> 0: Unknown
     *
     */
    struct MagneticFieldMsg {
        double time_stamp;                                             //!< Timestamp of data
        uint64_t seq;                                                  //!< Sequence Number
        fast::rf::messages::StandardMsgs::Vector3DMsg magnetic_field;  //!< Magnetic Field (Tesla)
        fast::rf::messages::StandardMsgs::Covariance3DMsg
            magnetic_field_covariance;  //!< Covariance Matrix of Magnetic Field
        MagneticFieldMsg() : time_stamp(-1.0), seq(0) {}

        /**
         * @brief Human readable string of the data
         *
         * @return std::string
         */
        std::string pretty() {
            std::string str = "T: " + std::to_string(time_stamp) + " S: " + std::to_string(seq) + "\n";
            str += "Magnetic Field:\n";
            str += "\t" + magnetic_field.pretty() + "\n";
            return str;
        }
    };
}  // namespace fast::rf::messages::SensorMsgs
