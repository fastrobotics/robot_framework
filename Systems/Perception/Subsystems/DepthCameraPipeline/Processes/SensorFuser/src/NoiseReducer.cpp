#include <CPUNoiseReducer.hpp>
#include <Infrastructure/Logger.hpp>
#include <NoiseReducer.hpp>
#ifdef ARCHITECTURE_JETSONNANO
#include <GPUNoiseReducer.hpp>
#endif

#include <exception>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser {
    bool NoiseReducer::init() {
        m_backend.reset();
#ifdef ARCHITECTURE_JETSONNANO
        if (GPUNoiseReducer::isAvailable()) {
            auto gpu_backend = std::make_unique<GPUNoiseReducer>();
            if (!gpu_backend->setConfig(m_config) || !gpu_backend->init()) {
                fast::rf::Logger::logError("GPU NoiseReducer was selected but failed to initialize.");
                return false;
            }
            fast::rf::Logger::logInfo("NoiseReducer selected the CUDA GPU backend.");
            m_backend = std::move(gpu_backend);
            return true;
        }
#endif
        auto cpu_backend = std::make_unique<CPUNoiseReducer>();
        if (!cpu_backend->setConfig(m_config) || !cpu_backend->init()) {
            fast::rf::Logger::logError("Unable to initialize CPU NoiseReducer backend.");
            return false;
        }
        fast::rf::Logger::logInfo("NoiseReducer selected the CPU backend.");
        m_backend = std::move(cpu_backend);
        return true;
    }

    bool NoiseReducer::setConfig(double voxelSize_m, double radius_m, uint64_t minNeighborCount) {
        NoiseReducerConfig config{voxelSize_m, radius_m, minNeighborCount};
        if (!isValidNoiseReducerConfig(config)) {
            fast::rf::Logger::logError(
                "NoiseReducer configuration requires positive finite sizes and a valid "
                "neighbor count.");
            return false;
        }
        if (m_backend && !m_backend->setConfig(config)) {
            fast::rf::Logger::logError("Selected NoiseReducer backend rejected its configuration.");
            return false;
        }
        m_config = config;
        return true;
    }

    fast::rf::messages::SensorMsgs::PointCloudMsg NoiseReducer::reduceNoise(
        const fast::rf::messages::SensorMsgs::PointCloudMsg& input) {
        if (!m_backend) {
            fast::rf::Logger::logError("NoiseReducer::init() must succeed before reduceNoise() is called.");
            throw std::logic_error("NoiseReducer has not been initialized.");
        }
        if (!input.point_cloud)
            fast::rf::Logger::logError("PointCloudMsg contains a null PCL point cloud.");

        try {
            return m_backend->reduceNoise(input);
        } catch (const std::exception& error) {
            fast::rf::Logger::logError("NoiseReducer backend failed: " + std::string(error.what()));
            throw;
        }
    }
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser
