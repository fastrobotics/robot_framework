#include <Infrastructure/Logger.hpp>
#include <ReadyToArmComputer.hpp>
namespace fast::rf::SafetySystem::ModeManagerSubsystem {
    bool ReadyToArmComputer::add_monitor(uint8_t systemID, uint8_t subsystemID, uint8_t processID) {
        [[maybe_unused]] std::size_t before_size = monitors.size();
        Monitor monitor = Monitor(systemID, subsystemID, processID);
        monitors.insert({monitor.key, monitor});
        std::size_t after_size = monitors.size();
        if (after_size > before_size) {
            return true;
        } else {
            fast::rf::Logger::log_error("Not able to add Monitor!");
            return false;
        }
    }
    bool ReadyToArmComputer::init() {
        if (monitors.size() > 0) {
            return true;
        } else {
            return false;
        }
    }
    std::string ReadyToArmComputer::pretty() {
        std::string str = "---Ready To Arm Computer---\n";
        str +=
            "\tT: " + std::to_string(current_time_sec) + " (sec) Ready To Arm: " + std::to_string(ready_to_arm) + "\n";
        str += "\tMonitors: " + std::to_string(monitors.size()) + "\n";
        uint16_t counter = 0;
        for (auto monitor : monitors) {
            str += "\t[" + std::to_string(counter) + "/" + std::to_string(monitors.size()) + "] " +
                   monitor.second.pretty() + "\n";
        }
        return str;
    }
    bool ReadyToArmComputer::update(double current_time_sec_) {
        current_time_sec = current_time_sec_;
        if (monitors.size() == 0) {
            ready_to_arm = false;
            fast::rf::Logger::log_warn("No Monitors Defined!  Won't be able to Arm.");
            return false;
        }
        bool all_ready_to_arm = true;
        for (auto monitor : monitors) {
            if (monitor.second.time_last_updated < 0) {
                fast::rf::Logger::log_warn(monitor.second.pretty() + " NEVER RECEIVED!");
                all_ready_to_arm = false;
            } else if (monitor.second.ready_to_arm == false) {
                fast::rf::Logger::log_warn(monitor.second.pretty() + " NOT READY!");
                all_ready_to_arm = false;
            } else {
                double time_since_last = current_time_sec - monitor.second.time_last_updated;
                if (time_since_last >= ReadyToArmComputer::PROCESS_TIMEOUT_SEC) {
                    monitor.second.ready_to_arm = false;
                    fast::rf::Logger::log_warn(monitor.second.pretty() + " TIMEOUT!");
                    all_ready_to_arm = false;
                }
            }
        }
        if (all_ready_to_arm == true) {
            ready_to_arm = true;
        } else {
            ready_to_arm = false;
        }
        return true;
    }
    bool ReadyToArmComputer::new_ArmedStatus([
        [maybe_unused]] fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg msg) {
        auto key = generate_key(msg.systemID, msg.subsystemID, msg.processID);
        auto it = monitors.find(key);
        if (it == monitors.end()) {
            fast::rf::Logger::log_warn("Monitor not initialized for: " + msg.pretty());
            return false;
        } else {
            it->second.ready_to_arm = msg.ready_to_arm;
            it->second.time_last_updated = current_time_sec;
        }
        return true;
    }
}  // namespace fast::rf::SafetySystem::ModeManagerSubsystem