/**
 * @file IGlobalPathStorageProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-Interface
 */
#pragma once
#include <DiagnosticMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>

namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem::GlobalPathStorage {
    /**
     * @brief Interface for the GlobalPathStorage Process
     *
     */
    class IGlobalPathStorageProcess {
       public:
        IGlobalPathStorageProcess() = default;
        virtual ~IGlobalPathStorageProcess() = default;

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
        virtual std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() = 0;
    };
}  // namespace fast::rf::NavigationSystem::GlobalPlannerSubsystem::GlobalPathStorage