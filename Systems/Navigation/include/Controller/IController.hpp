/**
 * @file IController.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-08-09
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <string>
/**
 * @brief Namespace for Controllers
 *
 */
namespace fast::rf::NavigationSystem::Controller {
    /**
     * @brief The type of Controller
     *
     */
    enum class ControllerType {
        UNKNOWN = 0,                     //!< Unknown Type
        PID_CONTROLLER = 1,              //!< PID Controller
        RELAY_AUTO_TUNE_CONTROLLER = 2,  //!< Relay Auto-Tune Controller
        END_OF_LIST = 3                  //!< End of List, used for Range Checks
    };
    /**
     * @brief Generic Controller Config interface
     *
     */
    class IControllerConfig {
       public:
        IControllerConfig() = default;
        virtual ~IControllerConfig() {}
        /**
         * @brief Validates if the config is ok
         *
         * @return true
         * @return false
         */
        virtual bool is_ok() = 0;

        /**
         * @brief Human readable string of data
         *
         * @return std::string
         */
        virtual std::string pretty() = 0;

        double get_max_output() { return max_output_; }

        double get_min_output() { return min_output_; }

       protected:
        double max_output_{0.0};  //!< Max Output Value
        double min_output_{0.0};  //!< Min Output Value
    };
    /**
     * @brief Generic Controller Output Interface
     *
     */
    class IControllerOutput {
       public:
        IControllerOutput() = default;
        virtual ~IControllerOutput() {}
        bool is_new{false};         //!< If the data is new
        double command_value{0.0};  //!< The command value of the controller
    };
    /**
     * @brief Generic Controller
     *
     */
    class IController {
       public:
        virtual ~IController() = default;
        /**
         * @brief Get the controller type
         *
         * @return ControllerType
         */
        virtual ControllerType get_controller_type() = 0;

        /**
         * @brief Initialize the Controller
         *
         * @return true
         * @return false
         */
        virtual bool init() = 0;

        /**
         * @brief Provide a new Set Point
         *
         * @param set_point
         * @param time_stamp_sec
         * @return true
         * @return false
         */
        virtual bool new_set_point(double set_point, double time_stamp_sec) = 0;
        /**
         * @brief Provide a new Sensor Input.  Generally a new output will be computed at this time
         *
         * @param sensor_input
         * @param time_stamp_sec
         * @return true
         * @return false
         */
        virtual bool new_sensor_input(double sensor_input, double time_stamp_sec) = 0;
        /**
         * @brief Update the object
         *
         * @param current_time_sec
         * @return true
         * @return false
         */
        virtual bool update(double current_time_sec) = 0;

        /**
         * @brief Get the sensor delta time sec, otherwise known as sampling time
         *
         * @return double
         */
        virtual double get_sensor_delta_time_sec() = 0;

        /**
         * @brief Get the output
         *
         * @return IControllerOutput*
         */
        virtual IControllerOutput* get_output() = 0;
        /**
         * @brief Print a human readable string
         *
         * @return std::string
         */
        virtual std::string pretty() = 0;

        virtual bool clear() = 0;
    };
}  // namespace fast::rf::NavigationSystem::Controller