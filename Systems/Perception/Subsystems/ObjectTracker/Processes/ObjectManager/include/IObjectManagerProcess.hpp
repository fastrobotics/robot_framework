/**
 * @file IObjectManagerProcess.hpp
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

namespace fast::rf::PerceptionSystem::ObjectTrackerSubsystem::ObjectManager {
    /**
     * @brief Interface for the ObjectManager fast::rf::Process
     *
     */
    class IObjectManagerProcess : public fast::rf::IProcess {
       public:
        IObjectManagerProcess() = default;
        virtual ~IObjectManagerProcess() = default;

        /**
         * @brief Initialize the object
         *
         * @return true
         * @return false
         */
        virtual bool init() = 0;
    };
}  // namespace fast::rf::PerceptionSystem::ObjectTrackerSubsystem::ObjectManager
