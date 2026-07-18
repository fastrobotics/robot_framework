#include <Infrastructure/Logger.hpp>
#include <ReadyToArmComputer.hpp>
namespace fast::rf::SafetySystem::ModeManagerSubsystem {
    bool ReadyToArmComputer::add_monitor(uint8_t systemID, uint8_t subsystemID, uint8_t componentID) {
        [[maybe_unused]] std::size_t before_size = monitors.size();
        Monitor monitor = Monitor(systemID, subsystemID, componentID);
        monitors[monitor.key] = monitor;
        std::size_t after_size = monitors.size();
        if (after_size > before_size) {
            return true;
        } else {
            fast::rf::Logger::log_error("Not able to add Monitor!");
            return false;
        }
    }
    bool ReadyToArmComputer::init() { return false; }
    std::string ReadyToArmComputer::pretty() { return ""; }
    bool ReadyToArmComputer::update([[maybe_unused]] double current_time_sec) { return false; }
    bool ReadyToArmComputer::new_ArmedStatus([
        [maybe_unused]] fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg msg) {
        return false;
    }
}  // namespace fast::rf::SafetySystem::ModeManagerSubsystem