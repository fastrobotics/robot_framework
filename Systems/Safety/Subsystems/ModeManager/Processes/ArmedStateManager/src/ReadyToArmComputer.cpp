#include <ReadyToArmComputer.hpp>
namespace fast::rf::SafetySystem::ModeManagerSubsystem {
    bool ReadyToArmComputer::add_monitor([[maybe_unused]] uint8_t systemID, [[maybe_unused]] uint8_t subystemID,
                                         [[maybe_unused]] uint8_t componentID) {
        return false;
    }
    bool ReadyToArmComputer::init() { return false; }
    std::string ReadyToArmComputer::pretty() { return ""; }
    bool ReadyToArmComputer::update([[maybe_unused]] double current_time_sec) { return false; }
    bool ReadyToArmComputer::get_ready_to_arm() { return false; }
    bool ReadyToArmComputer::new_ArmedStatus([
        [maybe_unused]] fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg msg) {
        return false;
    }
}  // namespace fast::rf::SafetySystem::ModeManagerSubsystem