/**
 * @file BasicSensorFuserProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-BasicHeader v0.1
 */
#pragma once

#include <BaseSensorFuserProcess.hpp>

namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {

    class BasicSensorFuserProcessConfig {
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
    }
    /**
     * @brief Minimal Implementation for a SensorFuser Process
     *
     */
    class BasicSensorFuserProcess : public BaseSensorFuserProcess {
       public:
        BasicSensorFuserProcess() : BaseSensorFuserProcess() {}

        /**
         * @brief Initialize the Object
         *
         * @return true
         * @return false
         */
        bool init() override;

        bool setConfig(BasicSensorFuserProcessConfig config) {
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

       private:
        BasicSensorFuserProcessConfig m_config;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser
