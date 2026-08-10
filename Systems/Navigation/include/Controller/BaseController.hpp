/**
 * @file BaseController.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-08-09
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <Controller/IController.hpp>
#include <Infrastructure/Logger.hpp>
namespace fast::rf::NavigationSystem::Controller {
    /**
     * @brief Abstract class that provides some common functionality
     *
     */
    class BaseController : public IController {
       public:
        /**
         * @brief Get the controller type
         *
         * @return ControllerType
         */
        ControllerType get_controller_type() override { return controller_type; }

        /**
         * @brief Get the sensor delta time sec
         *
         * @return double
         */
        double get_sensor_delta_time_sec() override { return delta_sensor_sample_time_sec; }

       protected:
        /**
         * @brief Initialize the abstract object.  Should be called by concrete class.
         *
         * @param config
         * @return true
         * @return false
         */
        bool init(IControllerConfig* config) override = 0;
        /**
         * @brief Generic update.  Should be called by concrete class.
         *
         * @param current_time_sec
         * @return true
         * @return false
         */
        bool update(double current_time_sec) override = 0;
        /**
         * @brief Process a set point.  Should be called by concrete class.
         *
         * @param set_point
         * @param time_stamp_sec
         * @return true
         * @return false
         */
        bool new_set_point(double set_point, double time_stamp_sec) override = 0;
        /**
         * @brief Process a sensor input.  Should be called by concrete class.
         *
         * @param sensor_input
         * @param time_stamp_sec
         * @return true
         * @return false
         */
        bool new_sensor_input(double sensor_input, double time_stamp_sec) override = 0;
        /**
         * @brief Human readable string.  Should be called by concrete class.
         *
         * @return std::string
         */
        std::string pretty() override = 0;

        IControllerConfig* config_{nullptr};  //!< Generic config container
        double latest_set_point{0.0};         //!< Latest Set Point
        double latest_sensor_input{0.0};      //!< Latest Sensor Input

       private:
        ControllerType controller_type{ControllerType::UNKNOWN};
        double sensor_timestamp_sec_{0.0};
        double delta_sensor_sample_time_sec{-1.0};
        double current_time_sec_{0.0};

        uint64_t sensor_rx_count{0};
        uint64_t setpoint_rx_count{0};
        uint64_t update_count{0};
    };
}  // namespace fast::rf::NavigationSystem::Controller