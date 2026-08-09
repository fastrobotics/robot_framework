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
         * @brief Human readable string
         *
         * @return std::string
         */
        std::string pretty() override;
    };
}  // namespace fast::rf::NavigationSystem::Controller