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
#include <Combiner.hpp>
#include <OverlapRemover.hpp>

namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {

    /**
     * @brief Configuration for the Basic Sensor Fuser
     *
     */
    class BasicSensorFuserProcessConfig {
       public:
        /**
         * @brief Check if the config is ok
         *
         * @return true
         * @return false
         */
        bool isOk() {
            if (m_settleTimeSec <= 0.0) {
                return false;
            }
            return true;
        }
        /**
         * @brief Human readable string
         *
         * @return std::string
         */
        std::string pretty() {
            std::string str = "Settle Time: " + std::to_string(m_settleTimeSec) + "\n";
            return str;
        }
        double m_settleTimeSec{5.0};  // How long to let the Process settle for before trusting any outputs
    };
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
        BasicSensorFuserProcessConfig getConfig() { return m_config; }
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
        /**
         * @brief Process a new Point Cloud
         *
         * @param msg
         * @param sensorIndex
         * @return true
         * @return false
         */
        bool newPointCloud(fast::rf::messages::SensorMsgs::PointCloudMsg msg, uint8_t sensorIndex);

       private:
        BasicSensorFuserProcessConfig m_config;
        Combiner m_combiner;
        OverlapRemover m_overlapRemover;
        uint64_t sensorFusionCyclesCount{0};
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser
