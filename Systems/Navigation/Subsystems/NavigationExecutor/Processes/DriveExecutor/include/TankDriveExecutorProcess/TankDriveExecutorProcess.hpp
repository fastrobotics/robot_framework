/**
 * @file TankDriveExecutorProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <BaseDriveExecutorProcess.hpp>
#include <IDriveExecutorOutput.hpp>
#include <TankDriveExecutorProcess/TankDriveExecutorOutput.hpp>

namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
/**
 * @brief Data Structure encoding Tank Drive Data
 *
 */

struct TankDriveData {
    double left_channel{0.0};   //!< Left Channel
    double right_channel{0.0};  //!< Right Channel
};

/**
 * @brief Data Structure encoding Tank Drive Channel Config
 *
 */
struct TankDriveChannelConfig {
    double min_value{-100.0};   //!< Min value of the channel
    double max_value{100.0};    //!< Max value of the channel
    double neutral_value{0.0};  //!< Neutral value of the channel
    TankDriveChannelConfig() : min_value(-100.0), neutral_value(0.0), max_value(100.0) {}
    TankDriveChannelConfig(double min, double neutral, double max)
        : min_value(min), neutral_value(neutral), max_value(max) {}
};

/**
 * @brief Minimal implementation for a DriveExecutor Process
 */
class TankDriveExecutorProcess : public BaseDriveExecutorProcess {
   public:
    TankDriveExecutorProcess() : left_channel_config(), right_channel_config(), BaseDriveExecutorProcess() {
        output = new TankDriveExecutorOutput();
    }
    /**
     * @brief Update with recent timing data
     *
     * @param current_time_sec
     * @param delta_time_sec
     * @return true If update executed ok
     * @return false If update executed with some error
     */
    bool update(double current_time_sec, double delta_time_sec) override;

    IDriveExecutorOutput* new_cmd(GeometryMsgs::TwistMsg cmd) override;

    TankDriveData convert(GeometryMsgs::TwistMsg twist);

    void set_config(TankDriveChannelConfig left_channel, TankDriveChannelConfig right_channel) {
        left_channel_config = left_channel;
        right_channel_config = right_channel;
    }

    double clip(double value, double min_value, double max_value);

   private:
    TankDriveChannelConfig left_channel_config;
    TankDriveChannelConfig right_channel_config;
    TankDriveExecutorOutput* output;
};
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem