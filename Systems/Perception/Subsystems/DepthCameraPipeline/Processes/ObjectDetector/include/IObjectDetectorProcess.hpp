/**
 * @file IObjectDetectorProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-Interface v0.1
 */

#pragma once
#include <Detection3DMsg.hpp>
#include <DiagnosticMsg.hpp>
#include <IProcess.hpp>
#include <PointCloudMsg.hpp>
#include <ReadyToArmStatusMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>

namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector {
    /**
     * @brief Interface for the ObjectDetector fast::rf::Process
     *
     */
    class IObjectDetectorProcess : public fast::rf::IProcess {
       public:
        IObjectDetectorProcess() = default;
        virtual ~IObjectDetectorProcess() = default;

        /**
         * @brief Initialize the object
         *
         * @return true
         * @return false
         */
        virtual bool init() = 0;

        virtual std::vector<fast::rf::messages::VisionMsgs::Detection3DMsg> detectObjects(
            fast::rf::messages::SensorMsgs::PointCloudMsg sensorCloud) = 0;
    };
}  // namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::ObjectDetector
