#include <Infrastructure/Logger.hpp>
#include <ReadyToArmComputer.hpp>
namespace fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager {
    bool ReadyToArmComputer::add_monitor(uint8_t systemID, uint8_t subsystemID, uint8_t processID) {
        std::size_t before_size = monitors.size();
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
            fast::rf::Logger::log_error("Can't Initialize, No Monitors Configured!");
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
            counter++;
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
        bool all_signals_rate_ok_ = true;
        bool all_signals_ever_received_ = true;
        for (auto monitor : monitors) {
            if (monitor.second.rx_count == 0) {
                fast::rf::Logger::log_warn(monitor.second.pretty() + " NEVER RECEIVED!");
                all_signals_ever_received_ = false;
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
                    all_signals_rate_ok_ = false;
                }
            }
        }
        all_signals_ever_received = all_signals_ever_received_;
        all_signals_rate_ok = all_signals_rate_ok_;
        if (all_ready_to_arm == true) {
            ready_to_arm = true;
        } else {
            ready_to_arm = false;
        }
        return true;
    }
    bool ReadyToArmComputer::new_ArmedStatus(fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg msg) {
        auto key = generate_key(msg.systemID, msg.subsystemID, msg.processID);
        auto it = monitors.find(key);
        if (it == monitors.end()) {
            fast::rf::Logger::log_error("Monitor not initialized for: " + msg.pretty());
            return false;
        } else {
            it->second.rx_count++;
            it->second.ready_to_arm = msg.ready_to_arm;
            it->second.time_last_updated = current_time_sec;
        }
        return true;
    }
}  // namespace fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager