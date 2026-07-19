/**
 * @file IGlobalPathRoutePlannerProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <DiagnosticMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>

namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem {
    /**
     * @brief Interface for the GlobalPathRoutePlanner Process
     *
     */
    class IGlobalPathRoutePlannerProcess {
       public:
        IGlobalPathRoutePlannerProcess() = default;
        virtual ~IGlobalPathRoutePlannerProcess() = default;

        /**
         * @brief Initialize the object
         *
         * @return true
         * @return false
         */
        virtual bool init() = 0;
        /**
         * @brief Generic Update function
         *
         * @param current_time_sec Current time stamp
         * @return true If the process updated ok
         * @return false If the process did not update ok
         */
        virtual bool update(double current_time_sec) = 0;

        /**
         * @brief Get the diagnostic object
         *
         * @return fast::rf::messages::InfrastructureMsgs::DiagnosticMsg
         */
        virtual std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() = 0;
    };
}  // namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem