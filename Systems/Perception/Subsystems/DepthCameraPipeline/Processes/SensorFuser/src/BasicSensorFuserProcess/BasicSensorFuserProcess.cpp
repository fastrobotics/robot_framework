/**
 * @compare_tag Process-BasicSource v0.1
 *
 */
#include <BasicSensorFuserProcess/BasicSensorFuserProcess.hpp>
#include <NoiseReducer/CPUNoiseReducer.hpp>
#ifdef ARCHITECTURE_JETSONNANO
#include <NoiseReducer/GPUNoiseReducer.hpp>
#endif
#include <chrono>
#include <memory>
namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {

    bool BasicSensorFuserProcess::newPointCloud(fast::rf::messages::SensorMsgs::PointCloudMsg msg,
                                                uint8_t sensorIndex) {
        bool status = m_combiner.newPointCloud(msg, sensorIndex);

        return status;
    }
    bool BasicSensorFuserProcess::init() {
        if (BaseSensorFuserProcess::init() == false) {
            fast::rf::Logger::logError("Unable to initialize Base Process.");
            return false;
        }
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
        diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::TIMING);
        if (m_diagnosticManager.initializeDiagnostics(diagnosticTypes) == false) {
            fast::rf::Logger::logError("Unable to initialize Diagnostic Manager.");
            return false;
        }
        if (m_config.isOk() == false) {
            fast::rf::Logger::logError("Config not Ok!");
            return false;
        }
        if (m_combiner.init() == false) {
            fast::rf::Logger::logError("Unable to initialize Combiner.");
            return false;
        }
        if (m_overlapRemover.init() == false) {
            fast::rf::Logger::logError("Unable to initialize Overlap Remover.");
            return false;
        }
#ifdef ARCHITECTURE_JETSONNANO
        m_noiseReducer = std::make_unique<GPUNoiseReducer>();
#else
        m_noiseReducer = std::make_unique<CPUNoiseReducer>();
#endif
        if (!m_noiseReducer->setConfig(NoiseReducerConfig{})) {
            fast::rf::Logger::logError("Unable to configure Noise Reducer.");
            return false;
        }
        if (m_noiseReducer->init() == false) {
            fast::rf::Logger::logError("Unable to initialize Noise Reducer.");
            return false;
        }
        return true;
    }
    bool BasicSensorFuserProcess::update(double currentTimeSec) {
        auto startTime = std::chrono::high_resolution_clock::now();
        if (BaseSensorFuserProcess::update(currentTimeSec) == false) {
            fast::rf::Logger::logWarn("Unable to update Base Sensor Fuser Process.");
            return false;
        }
        if (m_combiner.isCombinedPointCloudAvailable() == true) {
            auto combinedPointCloud = m_combiner.getCombinedPointCloud();
            auto overlapRemovedPointCloud = m_overlapRemover.removeOverlap(combinedPointCloud);
            m_fusedPointCloud = m_noiseReducer->reduceNoise(overlapRemovedPointCloud);
            m_fusedCloudAvailable = true;
            sensorFusionCyclesCount++;
        }
        auto endTime = std::chrono::high_resolution_clock::now();
        double computeTime = std::chrono::duration<double>(endTime - startTime).count();

        if (m_runTimeSec > m_config.m_settleTimeSec) {
            if (sensorFusionCyclesCount == 0) {
                m_diagnosticManager.updateDiagnostic(
                    fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::WARN,
                    fast::rf::DiagnosticDefinition::DiagnosticMessage::NODATA, "Have not performed Fusion Yet.");
            } else {
                if (computeTime > m_config.m_longFusionTimeSec) {
                    m_diagnosticManager.updateDiagnostic(
                        fast::rf::DiagnosticDefinition::DiagnosticType::TIMING, fast::rf::Level::WARN,
                        fast::rf::DiagnosticDefinition::DiagnosticMessage::DIAGNOSTIC_FAILED,
                        "Fusion Timing taking too long");
                } else {
                    m_diagnosticManager.updateDiagnostic(
                        fast::rf::DiagnosticDefinition::DiagnosticType::TIMING, fast::rf::Level::INFO,
                        fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Fusion Timing Ok");
                }
                m_diagnosticManager.updateDiagnostic(
                    fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE, fast::rf::Level::INFO,
                    fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR, "Running Fusion");
            }
        }

        return true;
    }
    std::string BasicSensorFuserProcess::pretty() {
        std::string str = "---Basic SensorFuser Process---";
        // str += BaseSensorFuserProcess::pretty();
        // str += m_config.pretty();
        // str += "Sensor Fusion Cycle Count: " + std::to_string(sensorFusionCyclesCount) + "\n";
        return str;
    }

}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser
