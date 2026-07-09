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
#include <string>
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
        /**
         * @brief Pretty print data
         *
         * @return std::string
         */
        std::string pretty() {
            std::string str = "Axes:\n";
            for (std::size_t i = 0; i < axes.size(); ++i) {
                str += "\t[" + std::to_string(i) + "/" + std::to_string(axes.size()) + "]: " + std::to_string(axes[i]) +
                       "\n";
            }
            return str;
        }
    };
}  // namespace fast::rf::messages::SensorMsgs
