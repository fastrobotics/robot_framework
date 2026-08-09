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
    class BaseController : public IController {
       public:
        ControllerType get_controller_type() { return controller_type; }

       protected:
        bool init(IControllerConfig* config) override = 0;
        std::string pretty() override = 0;
        IControllerConfig* config_{nullptr};

       private:
        ControllerType controller_type{ControllerType::UNKNOWN};
    };
}  // namespace fast::rf::NavigationSystem::Controller