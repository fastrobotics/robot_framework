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
    double min_value{-100.0};   //!< Min value Pof the channel
    double max_value{100.0};    //!< Max value of the channel
    double neutral_value{0.0};  //!< Neutral value of the channel
    TankDriveChannelConfig() : min_value(-100.0), neutral_value(0.0), max_value(100.0) {}
    /**
     * @brief Instantiate the Channel Config
     * @param min Minimum Value
     * @param neutral Neutral Value
     * @param max Max Value
     */
    TankDriveChannelConfig(double min, double neutral, double max)
        : min_value(min), neutral_value(neutral), max_value(max) {}  //!< Function to initialize
};
/**
 * @brief Process for Tank Drive Executor
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

    /**
     * @brief Convert a Twist to a Tank Drive Output
     * @param twist The twist data
     * @return The Tank Drive Data
     */
    TankDriveData convert(GeometryMsgs::TwistMsg twist);  //!< Convert a Twist to Tank Drive Outputs

    /**
     * @brief Initialize the Process with the correct Channel Config
     * @param left_channel Left Channel Config
     * @param right_channel Right Channel Config
     */
    void set_config(TankDriveChannelConfig left_channel, TankDriveChannelConfig right_channel) {
        left_channel_config = left_channel;
        right_channel_config = right_channel;
    }
    /**
     * @brief Clip a value to be with boundaries
     *
     * @param value The value to convert
     * @param min_value Minimum Value
     * @param max_value Maximum Value
     * @return double Converted Value
     */

    double clip(double value, double min_value, double max_value);

   private:
    TankDriveChannelConfig left_channel_config;
    TankDriveChannelConfig right_channel_config;
    TankDriveExecutorOutput* output;
};
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem