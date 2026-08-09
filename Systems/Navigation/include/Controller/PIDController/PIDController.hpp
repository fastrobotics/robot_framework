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
    class PIDController : public BaseController {
       public:
        bool init(IControllerConfig config) override;
        std::string pretty() override;
    };
}  // namespace fast::rf::NavigationSystem::Controller