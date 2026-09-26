/**
 * @file IDepthCameraFeatureHandlerProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-Interface v0.1
 */

#pragma once
#include <DiagnosticMsg.hpp>
#include <IProcess.hpp>
#include <ReadyToArmStatusMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>

namespace fast::rf::PerceptionSystem::ObjectTrackerSubsystem::DepthCameraFeatureHandler {
    /**
     * @brief Interface for the DepthCameraFeatureHandler fast::rf::Process
     *
     */
    class IDepthCameraFeatureHandlerProcess : public fast::rf::IProcess {
       public:
        IDepthCameraFeatureHandlerProcess() = default;
        virtual ~IDepthCameraFeatureHandlerProcess() = default;

        /**
         * @brief Initialize the object
         *
         * @return true
         * @return false
         */
        virtual bool init() = 0;
    };
}  // namespace fast::rf::PerceptionSystem::ObjectTrackerSubsystem::DepthCameraFeatureHandler
