#include <Controller/BaseController.hpp>
namespace fast::rf::NavigationSystem::Controller {
    bool BaseController::init(IControllerConfig* config) {
        if (config == nullptr) {
            return false;
        }
        config_ = config;
        return true;
    }
    std::string BaseController::pretty() {
        std::string str = "---Base Controller---\n";
        str += "\tController Type: " + std::to_string((uint8_t)controller_type) + "\n";
        return str;
    }
}  // namespace fast::rf::NavigationSystem::Controller