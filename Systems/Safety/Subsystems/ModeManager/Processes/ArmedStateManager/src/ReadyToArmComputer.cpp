#include <Infrastructure/Logger.hpp>
#include <ReadyToArmComputer.hpp>
namespace fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager {
    bool ReadyToArmComputer::add_monitor(fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg msg) {
        std::size_t before_size = monitors.size();
        Monitor monitor = Monitor(msg.systemID, msg.subsystemID, msg.processID);
        monitor.rx_count = 1;
        monitor.ready_to_arm = msg.ready_to_arm;
        monitor.time_last_updated = current_time_sec;
        monitors.insert({monitor.key, monitor});
        std::size_t after_size = monitors.size();

        if (after_size > before_size) {
            return true;
        }
        // GCOV_EXCL_START
        // Key should already be guaranteed to be unique, so this shouldn't be possible.  But keep as a safe-guard.
        else {
            fast::rf::Logger::log_error("Not able to add Monitor!");
            return false;
        }
        // GCOV_EXCL_STOP
    }
    bool ReadyToArmComputer::init() { return true; }
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
        if (expected_ready_to_arm_signals_ == 0) {
            ready_to_arm = false;
            fast::rf::Logger::log_error("Expected Ready To Arm Signals == 0!  Need to configure!");
            return false;
        }
        if (expected_ready_to_arm_signals_ > monitors.size()) {
            ready_to_arm = false;
            fast::rf::Logger::log_warn("Not all Ready to Arm Signals Received Yet.");
            return true;
        }
        if (monitors.size() > expected_ready_to_arm_signals_) {
            fast::rf::Logger::log_notice("Receiving more Ready To Arm Signals than Expected.");
        }
        bool all_ready_to_arm = true;
        bool all_signals_rate_ok_ = true;
        bool all_signals_ever_received_ = true;
        for (auto monitor : monitors) {
            // GCOV_EXCL_START
            // Shouldn't be possible since add_monitor() is only ran when it's already received, but this is a
            // safe-guard
            if (monitor.second.rx_count == 0) {
                fast::rf::Logger::log_warn(monitor.second.pretty() + " NEVER RECEIVED!");
                all_signals_ever_received_ = false;
                all_ready_to_arm = false;
            }
            // GCOV_EXCL_STOP
            else if (monitor.second.ready_to_arm == false) {
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
        if ((msg.systemID == 0) || (msg.subsystemID == 0) || (msg.processID == 0)) {
            fast::rf::Logger::log_warn("Armed Status Message has undefined data: " + msg.pretty());
            return false;
        }
        auto key = generate_key(msg.systemID, msg.subsystemID, msg.processID);
        auto it = monitors.find(key);
        if (it == monitors.end()) {
            // GCOV_EXCL_START
            // Shouldn't be possible, since this is checking for a unique key, but it has to be unique because we
            // couldn't find it.  But this is a safe-guard.
            if (add_monitor(msg) == false) {
                fast::rf::Logger::log_error("Unable to add Monitor for: " + msg.pretty());
                return false;
            }
            // GCOV_EXCL_STOP
        } else {
            it->second.rx_count++;
            it->second.ready_to_arm = msg.ready_to_arm;
            it->second.time_last_updated = current_time_sec;
        }
        return true;
    }
}  // namespace fast::rf::SafetySystem::ModeManagerSubsystem::ArmedStateManager