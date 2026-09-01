/**
 * @file ITrajectoryControllerProcess.hpp
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
#include <OdomMsg.hpp>
#include <ReadyToArmStatusMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <TwistMsg.hpp>
#include <vector>

namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectoryController {
    /**
     * @brief Interface for the TrajectoryController Process
     *
     */
    class ITrajectoryControllerProcess : public fast::rf::IProcess {
       public:
        ITrajectoryControllerProcess() = default;
        virtual ~ITrajectoryControllerProcess() = default;
        /**
         * @brief Initialize the object
         *
         * @return true
         * @return false
         */
        virtual bool init() = 0;

        /**
         * @brief Process a new pose
         *
         * @param pose
         * @return true
         * @return false
         */
        virtual bool new_pose(fast::rf::messages::GeometryMsgs::OdomMsg pose) = 0;

        /**
         * @brief Process a new desired command
         *
         * @param cmd
         * @return true
         * @return false
         */
        virtual bool new_desired_command(fast::rf::messages::GeometryMsgs::TwistMsg cmd) = 0;

        /**
         * @brief Get the command data
         *
         * @param cmd
         * @return true if New
         * @return false  if Not
         */
        virtual bool get_command(fast::rf::messages::GeometryMsgs::TwistMsg& cmd) = 0;
    };
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem::TrajectoryController
