/**
 * @file DepthCameraPipelineSubsystem.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-10-05
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <BasicFeatureDetectorProcess/BasicFeatureDetectorProcess.hpp>
#include <BasicSensorFuserProcess/BasicSensorFuserProcess.hpp>
#include <Infrastructure/Logger.hpp>
#include <ObjectDetectorProcess.hpp>
#include <PointCloudMsg.hpp>
#include <ReadyToArmStatusMsg.hpp>
#include <SensorHealthMonitorProcess.hpp>
#include <SensorInputHandlerProcess.hpp>
#include <memory>
#include <string>
#include <unordered_map>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem {
    /**
     * @brief This runs the entire DepthCamera Pipeline Subsystem
     *
     */
    class DepthCameraPipelineSubsystem {
       public:
        struct DepthCameraPipelineSubsystemOutput {
            fast::rf::messages::SensorMsgs::PointCloudMsg latestFeatureCloud;
            std::vector<fast::rf::messages::VisionMsgs::Detection3DMsg> latestDetections;
            uint64_t fullPipelineOutputCounter{0};
        };
        class UpdateTimings {
           public:
            double fusedOutputRetrievalSec{0.0};
            double featureDetectionSec{0.0};
            double objectDetectionSec{0.0};
            double outputUpdateSec{0.0};
            double processUpdatesSec{0.0};
            double totalSec{0.0};
            bool visionPipelineExecuted{false};

            void addSample(const UpdateTimings& sample) {
                m_sampleCount++;
                const double count = static_cast<double>(m_sampleCount);
                fusedOutputRetrievalSec += (sample.fusedOutputRetrievalSec - fusedOutputRetrievalSec) / count;
                processUpdatesSec += (sample.processUpdatesSec - processUpdatesSec) / count;
                totalSec += (sample.totalSec - totalSec) / count;
                if (sample.visionPipelineExecuted) {
                    m_visionSampleCount++;
                    const double visionCount = static_cast<double>(m_visionSampleCount);
                    featureDetectionSec += (sample.featureDetectionSec - featureDetectionSec) / visionCount;
                    objectDetectionSec += (sample.objectDetectionSec - objectDetectionSec) / visionCount;
                    outputUpdateSec += (sample.outputUpdateSec - outputUpdateSec) / visionCount;
                }
                visionPipelineExecuted = sample.visionPipelineExecuted;
            }

            std::string pretty() const {
                return "DepthCameraPipeline update timing averages (s, samples=" + std::to_string(m_sampleCount) +
                       ", vision_samples=" + std::to_string(m_visionSampleCount) +
                       "): fused_output=" + std::to_string(fusedOutputRetrievalSec) +
                       ", feature_detection=" + std::to_string(featureDetectionSec) +
                       ", object_detection=" + std::to_string(objectDetectionSec) +
                       ", output_update=" + std::to_string(outputUpdateSec) +
                       ", process_updates=" + std::to_string(processUpdatesSec) +
                       ", total=" + std::to_string(totalSec) +
                       ", vision_pipeline_executed=" + (visionPipelineExecuted ? "true" : "false");
            }

           private:
            uint64_t m_sampleCount{0};
            uint64_t m_visionSampleCount{0};
        };
        DepthCameraPipelineSubsystem()
            : m_sensorInputHandlerProcess(std::make_shared<fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::
                                                               SensorInputHandler::SensorInputHandlerProcess>()),
              m_sensorHealthMonitorProcess(std::make_shared<fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::
                                                                SensorHealthMonitor::SensorHealthMonitorProcess>()),
              m_sensorFuserProcess(std::make_shared<fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::
                                                        SensorFuser::BasicSensorFuserProcess>()),
              m_featureDetectorProcess(std::make_shared<fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::
                                                            FeatureDetector::BasicFeatureDetectorProcess>()),
              m_objectDetectorProcess(std::make_shared<fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::
                                                           ObjectDetector::ObjectDetectorProcess>()) {
            m_pipeline["input_handler"] = m_sensorInputHandlerProcess;
            m_pipeline["health_monitor"] = m_sensorHealthMonitorProcess;
            m_pipeline["sensor_fuser"] = m_sensorFuserProcess;
            //  m_pipeline["feature_detector"] = m_featureDetectorProcess;
            // m_pipeline["object_detector"] = m_objectDetectorProcess;
            m_readyToArm.systemID = fast::rf::PerceptionSystem::SYSTEM_ID;
            m_readyToArm.subsystemID = fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SUBSYSTEM_ID;
            m_readyToArm.processID = 0;  // Entire Subsystem
        }
        /**
         * @brief Initialize the Subsystem
         *
         * @return true
         * @return false
         */
        bool init();
        /**
         * @brief Add Signals to Monitor
         *
         * @param signalName
         * @param datatype
         * @param expectedRateHz
         * @param rateTolerancePerc
         * @return true
         * @return false
         */
        bool addSignalToMonitor(std::string signalName, std::string datatype, double expectedRateHz,
                                double rateTolerancePerc) {
            return m_sensorHealthMonitorProcess->addSignalToMonitor(signalName, datatype, expectedRateHz,
                                                                    rateTolerancePerc);
        }
        DepthCameraPipelineSubsystemOutput getOutput() { return m_output; }
        /**
         * @brief Process a new Point Cloud
         *
         * @param msg
         * @param sensorName
         * @return true
         * @return false
         */
        bool newPointCloud(fast::rf::messages::SensorMsgs::PointCloudMsg msg, std::string sensorName);

        /**
         * @brief Human readable output of the subsystem
         *
         * @return std::string
         */
        std::string pretty();
        /**
         * @brief Update the subsystem at a regular rate
         *
         * @param currentTimeSec
         * @return true
         * @return false
         */
        bool update(double currentTimeSec);
        /**
         * @brief Get running average timings across update calls, in seconds.
         *
         * Vision-stage timings include zero samples when no fused point cloud was available.
         */
        UpdateTimings getUpdateTimings() const { return m_updateTimings; }
        /**
         * @brief Get the ready to arm object
         *
         * @return fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg
         */
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() { return m_readyToArm; }
        /**
         * @brief Get the Diagnostics object
         *
         * @return std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
         */
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics();

       private:
        std::shared_ptr<
            fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorInputHandler::SensorInputHandlerProcess>
            m_sensorInputHandlerProcess;
        std::shared_ptr<
            fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorHealthMonitor::SensorHealthMonitorProcess>
            m_sensorHealthMonitorProcess;
        std::shared_ptr<fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser::BasicSensorFuserProcess>
            m_sensorFuserProcess;
        std::shared_ptr<
            fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::FeatureDetector::BasicFeatureDetectorProcess>
            m_featureDetectorProcess;
        std::shared_ptr<fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector::ObjectDetectorProcess>
            m_objectDetectorProcess;
        std::unordered_map<std::string, std::shared_ptr<fast::rf::IProcess>> m_pipeline;
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg m_readyToArm;

        DepthCameraPipelineSubsystemOutput m_output;
        UpdateTimings m_updateTimings;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem