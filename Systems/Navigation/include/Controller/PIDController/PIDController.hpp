/**
 * @file PIDController.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-08-09
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <Controller/BaseController.hpp>
namespace fast::rf::NavigationSystem::Controller {
    /**
     * @brief Configuration for the PID Controller
     *
     */
    class PIDControllerConfig : public IControllerConfig {
       public:
        ~PIDControllerConfig() override {}
        /**
         * @brief Set the parameters
         *
         * @param P Proportional Constant
         * @param I Integration Constant
         * @param D Derivative Constant
         * @param sensor_scale_factor How much to scale Sensor Value by
         */
        void set_parameters(double P, double I, double D, double sensor_scale_factor) {
            K_P = P;
            K_I = I;
            K_D = D;
            sensor_scale = sensor_scale_factor;
        }

        double K_P{0.0};           //!< Proportional Constant
        double K_I{0.0};           //!< Integration Constant
        double K_D{0.0};           //!< Derivative Contant
        double sensor_scale{1.0};  //!< Sensor Scale Factor
    };
    /**
     * @brief Output Object
     *
     */
    class PIDControllerOutput : public IControllerOutput {
       public:
        ~PIDControllerOutput() override {}
        double setpoint_sensor_error{0.0};  //!< Difference between Set Point and Sensor Value
        double P_term{0.0};                 //!< Proportional Term
        double I_term{0.0};                 //!< Integration Term
        double D_term{0.0};                 //!< Derivative Term
    };
    /**
     * @brief A PID Controller
     *
     */
    class PIDController : public BaseController {
       public:
        /**
         * @brief Initialize the object
         *
         * @param config
         * @return true
         * @return false
         */
        bool init(IControllerConfig* config) override;

        /**
         * @brief Process a new set point
         *
         * @param set_point
         * @param time_stamp_sec
         * @return true
         * @return false
         */
        bool new_set_point(double set_point, double time_stamp_sec) override;

        /**
         * @brief Process a new sensor input.
         *
         * @param sensor_input
         * @param time_stamp_sec
         * @return true
         * @return false
         */
        bool new_sensor_input(double sensor_input, double time_stamp_sec) override;
        /**
         * @brief Update the object
         *
         * @param current_time_sec
         * @return true
         * @return false
         */
        bool update(double current_time_sec) override;

        /**
         * @brief Get the output
         *
         * @return PIDControllerOutput*
         */
        PIDControllerOutput* get_output() override;

        /**
         * @brief Human readable string
         *
         * @return std::string
         */
        std::string pretty() override;

       private:
        PIDControllerOutput* output_{nullptr};
    };
}  // namespace fast::rf::NavigationSystem::Controller