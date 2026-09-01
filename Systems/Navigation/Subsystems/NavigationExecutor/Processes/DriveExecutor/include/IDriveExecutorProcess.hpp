/**
 * @file IDriveExecutorProcess.hpp
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
#include <IDriveExecutorOutput.hpp>
#include <IProcess.hpp>
#include <ReadyToArmStatusMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <TwistMsg.hpp>
#include <vector>

using namespace fast::rf::messages;
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::DriveExecutor {
    /**
     * @brief Interface for the DriveExecutor Process
     *
     */
    class IDriveExecutorProcess : public fast::rf::IProcess {
       public:
        IDriveExecutorProcess() = default;
        virtual ~IDriveExecutorProcess() = default;

        /**
         * @brief Initialize the object
         *
         * @return true
         * @return false
         */
        virtual bool init() = 0;

        /**
         * @brief Generic Function for Drive Executor to process
         *
         * @param cmd Command to process
         * @return IDriveExecutorOutput* Abstract type
         */

        virtual IDriveExecutorOutput* new_cmd(GeometryMsgs::TwistMsg cmd) = 0;

        /**
         * @brief Get the most recent output
         *
         * @return IDriveExecutorOutput*
         */
        virtual IDriveExecutorOutput* get_output() = 0;
    };
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::DriveExecutor
