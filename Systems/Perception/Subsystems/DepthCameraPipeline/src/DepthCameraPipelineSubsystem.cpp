#include <DepthCameraPipelineSubsystem.hpp>
#include <chrono>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem {
    bool DepthCameraPipelineSubsystem::init() {
        if (m_sensorHealthMonitorProcess->init() == false) {
            fast::rf::Logger::logError("Unable to initialize Sensor Health Monitor!");
            return false;
        }
        if (m_sensorInputHandlerProcess->init() == false) {
            fast::rf::Logger::logError("Unable to initialize Sensor Input Handler!");
            return false;
        }
        if (m_sensorFuserProcess->init() == false) {
            fast::rf::Logger::logError("Unable to initialize Sensor Fuser!");
            return false;
        }
        if (m_featureDetectorProcess->init() == false) {
            fast::rf::Logger::logError("Unable to initialize Feature Detector!");
            return false;
        }
        if (m_objectDetectorProcess->init() == false) {
            fast::rf::Logger::logError("Unable to initialize Object Detector!");
            return false;
        }
        return true;
    }
    std::string DepthCameraPipelineSubsystem::pretty() {
        std::string str = "\n--- Depth Camera Pipeline Subsystem---\n";
        str += "\tReady To Arm: " + std::to_string(m_readyToArm.ready_to_arm) + "\n";
        for (auto process : m_pipeline) {
            str += process.second->pretty();
        }
        return str;
    }
    bool DepthCameraPipelineSubsystem::newPointCloud(fast::rf::messages::SensorMsgs::PointCloudMsg msg,
                                                     std::string sensorName) {
        if (m_sensorHealthMonitorProcess.get()->newPointCloud(sensorName, msg) == false) {
            fast::rf::Logger::logWarn("Unable to process Sensor Point Cloud Signal: " + sensorName);
            return false;
        }
        auto convertedCloud = m_sensorInputHandlerProcess.get()->newPointCloud(msg);
        if (!m_sensorFuserProcess->newPointCloud(convertedCloud, 0)) {
            fast::rf::Logger::logWarn("Unable to send Point Cloud to Sensor Fuser: " + sensorName);
            return false;
        }
        return true;
    }
    bool DepthCameraPipelineSubsystem::update(double currentTimeSec) {
        const auto updateStart = std::chrono::steady_clock::now();
        UpdateTimings timingSample;
        auto stepStart = std::chrono::steady_clock::now();
        auto fusedPointCloudOutput = m_sensorFuserProcess->getOutput();
        auto stepEnd = std::chrono::steady_clock::now();
        timingSample.fusedOutputRetrievalSec = std::chrono::duration<double>(stepEnd - stepStart).count();
        if (fusedPointCloudOutput.fusedPointCloudCounter > 0) {
            timingSample.visionPipelineExecuted = true;

            stepStart = std::chrono::steady_clock::now();
            auto featureCloud = m_featureDetectorProcess->detectFeatures(fusedPointCloudOutput.latestFusedPointCloud);
            stepEnd = std::chrono::steady_clock::now();
            timingSample.featureDetectionSec = std::chrono::duration<double>(stepEnd - stepStart).count();

            stepStart = std::chrono::steady_clock::now();
            auto detections = m_objectDetectorProcess->detectObjects(featureCloud);
            stepEnd = std::chrono::steady_clock::now();
            timingSample.objectDetectionSec = std::chrono::duration<double>(stepEnd - stepStart).count();

            stepStart = std::chrono::steady_clock::now();
            if (featureCloud.isValidFeatureCloud()) {
                m_output.latestFeatureCloud = featureCloud;
                m_output.latestDetections = detections;
                m_output.fullPipelineOutputCounter++;
            } else {
                fast::rf::Logger::logWarn("No Valid Feature Cloud Yet.");
            }
            stepEnd = std::chrono::steady_clock::now();
            timingSample.outputUpdateSec = std::chrono::duration<double>(stepEnd - stepStart).count();
        } else {
            fast::rf::Logger::logWarn("No Fused Point Cloud Yet.");
        }

        bool readyToArmFlag = true;
        bool updateSuccess = true;
        stepStart = std::chrono::steady_clock::now();
        for (auto& process : m_pipeline) {
            if (process.second->update(currentTimeSec) == false) {
                fast::rf::Logger::logWarn("Unable to update process: " + process.first);
                updateSuccess = false;
                break;
            }
            if (process.second->get_ready_to_arm().ready_to_arm == false) {
                readyToArmFlag = false;
            }
        }
        stepEnd = std::chrono::steady_clock::now();
        timingSample.processUpdatesSec = std::chrono::duration<double>(stepEnd - stepStart).count();
        if (updateSuccess) {
            m_readyToArm.ready_to_arm = readyToArmFlag;
        }

        stepEnd = std::chrono::steady_clock::now();
        timingSample.totalSec = std::chrono::duration<double>(stepEnd - updateStart).count();
        m_updateTimings.addSample(timingSample);
        fast::rf::Logger::logDebug(m_updateTimings.pretty());
        return updateSuccess;
    }
    std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> DepthCameraPipelineSubsystem::getDiagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> allDiagnostics;
        for (auto& process : m_pipeline) {
            auto diagnostics = process.second->getDiagnostics();
            allDiagnostics.insert(allDiagnostics.end(), diagnostics.begin(), diagnostics.end());
        }
        return allDiagnostics;
    }

}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem