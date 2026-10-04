/**
 * @file SensorHealthMonitorProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-Header v0.1
 */
#pragma once

#include <BaseSensorHealthMonitorProcess.hpp>
#include <PointCloudMsg.hpp>

namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorHealthMonitor {

    class SensorHealthMonitorProcessConfig {
       public:
        bool isOk() {
            // Add checks here
            return false;
        }
        std::string pretty() {
            std::string str = "";
            // Add string generation here
            return str;
        }

       private:
        // Add attributes here
    };
    /**
     * @brief Minimal Implementation for a SensorHealthMonitor Process
     *
     */
    class SensorHealthMonitorProcess : public BaseSensorHealthMonitorProcess {
       public:
        SensorHealthMonitorProcess() : BaseSensorHealthMonitorProcess() {}

        /**
         * @brief Initialize the Object
         *
         * @return true
         * @return false
         */
        bool init() override;

        bool setConfig(SensorHealthMonitorProcessConfig config) {
            if (config.isOk() == false) {
                fast::rf::Logger::logError("Unable to set Config! " + config.pretty());
                return false;
            }
            m_config = config;
            return true;
        }
        /**
         * @brief Update with recent timing data
         *
         * @param currentTimeSec
         * @return true If update executed ok
         * @return false If update executed with some error
         */
        bool update(double currentTimeSec) override;

        /**
         * @brief Human readable status of object
         *
         * @return std::string
         */
        std::string pretty() override;

        bool newPointCloudMsg(std::string name, fast::rf::messages::SensorMsgs::PointCloudMsg msg);

       private:
        SensorHealthMonitorProcessConfig m_config;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorHealthMonitor
