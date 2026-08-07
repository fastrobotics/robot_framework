/**
 * @file JoystickScaler.hpp
 * @author David Gitz
 * @brief
 * @version 0.1
 * @date 2026-07-08
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <ITeleopControlProcess.hpp>
#include <JoyMsg.hpp>
namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem {
    /**
     * @brief Scales Joystick Data to a common definition
     *
     */
    class JoystickScaler {
       public:
        static constexpr double AXIS_MAX_VALUE = 1.0;  //!< The Max value of the Axis
        /**
         * @brief Initialize the object
         *
         * @param device
         * @param joy_calibration_data
         * @return true
         * @return false
         */
        bool init(ControlDevice device, JoystickCalibrationData joy_calibration_data);
        /**
         * @brief Process a Joystick message
         *
         * @param joy
         * @return fast::rf::messages::SensorMsgs::JoyMsg
         */
        fast::rf::messages::SensorMsgs::JoyMsg new_joy(fast::rf::messages::SensorMsgs::JoyMsg joy);
        /**
         * @brief Scale a value linearly
         *
         * @param input_value
         * @param input_min
         * @param input_max
         * @param output_min
         * @param output_max
         * @return double
         */
        static double scale_value(double input_value, double input_min, double input_max, double output_min,
                                  double output_max);

       private:
        ControlDevice control_device{ControlDevice::UNKNOWN};  //!< The device that is being used
        bool is_initialized{false};                            //!< If the object is initialized
        JoystickCalibrationData joy_cal_data;                  //!< Joystick Calibration INformation
    };

}  // namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem