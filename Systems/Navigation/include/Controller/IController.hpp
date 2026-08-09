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
namespace fast::rf::NavigationSystem::Controller {
    enum class ControllerType { UNKNOWN = 0, PID_CONTROLLER = 1, END_OF_LIST = 2 };
    class IControllerConfig {
        IControllerConfig() = default;
        virtual ~IControllerConfig() = default;
    };
    class IControllerOutput {};
    class IController {
       public:
        virtual ControllerType get_controller_type() = 0;
        virtual bool init(IControllerConfig* config) = 0;
        virtual std::string pretty() = 0;
    };
}  // namespace fast::rf::NavigationSystem::Controller