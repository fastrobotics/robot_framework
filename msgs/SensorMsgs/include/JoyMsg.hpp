/**
 * @file JoyMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-08
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <cstdint>
#include <vector>
namespace fast::rf::messages::SensorMsgs {
    /**
     * @brief Joystick Data Structure
     *
     */
    struct JoyMsg {
        double time_stamp;              //!< Timestamp
        std::vector<double> axes;       //!< Data representing Joystick Axes
        std::vector<uint32_t> buttons;  //!< Data representing Joystick Buttons
        JoyMsg() {}
    };
}  // namespace fast::rf::messages::SensorMsgs
