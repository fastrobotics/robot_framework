#include <Controller/PIDController/PIDController.hpp>
namespace fast::rf::NavigationSystem::Controller {
    bool PIDController::init(IControllerConfig config) {
        bool status = BaseController::init(config);
        if (status == false) {
            return false;
        }
        return true;
    }
    std::string PIDController::pretty() {
        std::string str = "---PID Controller---\n";
        str += BaseController::pretty();
        return str;
    }
}  // namespace fast::rf::NavigationSystem::Controller