/**
 * @file BasicObjectDetectorProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-BasicHeader v0.1
 */
#pragma once

#include <BaseObjectDetectorProcess.hpp>
#include <ObjectExtractor/IObjectExtractor.hpp>

namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector {

    class ObjectDetectorProcessConfig {
       public:
        double m_clusterToleranceDeg{3.0f};
        uint64_t m_minClusterSize{50};
        uint64_t m_maxPointCloudSize{1000000};
        bool isOk() {
            // Add checks here
            return false;
        }
        std::string pretty() {
            std::string str = "Config:\n";
            str += "\tCluster Tolerance: " + std::to_string(m_clusterToleranceDeg) + " (deg)\n";
            str += "\tMin Cluster Size: " + std::to_string(m_minClusterSize) + "\n";
            str += "\tMax Point Cloud Size: " + std::to_string(m_maxPointCloudSize) + " (points) \n";
            return str;
        }

       private:
        // Add attributes here
    };
    /**
     * @brief Minimal Implementation for a ObjectDetector Process
     *
     */
    class ObjectDetectorProcess : public BaseObjectDetectorProcess {
       public:
        ObjectDetectorProcess() : BaseObjectDetectorProcess() {}

        /**
         * @brief Initialize the Object
         *
         * @return true
         * @return false
         */
        bool init() override;

        bool setConfig(ObjectDetectorProcessConfig config) {
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

        std::vector<fast::rf::messages::VisionMsgs::Detection3DMsg> detectObjects(
            fast::rf::messages::SensorMsgs::PointCloudMsg sensorCloud) override;

       private:
        ObjectDetectorProcessConfig m_config;
        std::unique_ptr<IObjectExtractor> m_objectExtractor;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector
