/**
 * @file BasicExampleProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-BasicHeader v0.1
 */
#pragma once

#include <BaseExampleProcess.hpp>

namespace fast::rf::ExampleSystem::ExampleSubsystem::Example {

    class BasicExampleProcessConfig {
       public:
        bool isOk() {
            // Add checks here
            return false;
        }
        std::string pretty() {
            std::string str = "";
            // Add string generation here
            return str;
        }

       private:
        // Add attributes here
    };
    /**
     * @brief Minimal Implementation for a Example Process
     *
     */
    class BasicExampleProcess : public BaseExampleProcess {
       public:
        BasicExampleProcess() : BaseExampleProcess() {}

        /**
         * @brief Initialize the Object
         *
         * @return true
         * @return false
         */
        bool init() override;

        bool setConfig(BasicExampleProcessConfig config) {
            if (config.isOk() == false) {
                fast::rf::Logger::logError("Unable to set Config! " + config.pretty());
                return false;
            }
            m_config = config;
            return true;
        }
        /**
         * @brief Update with recent timing data
         *
         * @param currentTimeSec
         * @return true If update executed ok
         * @return false If update executed with some error
         */
        bool update(double currentTimeSec) override;

        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() {
            return m_diagnosticManager.getDiagnostics();
        }

        /**
         * @brief Human readable status of object
         *
         * @return std::string
         */
        std::string pretty() override;

       private:
        BasicExampleProcessConfig m_config;
    };
}  // namespace fast::rf::ExampleSystem::ExampleSubsystem::Example
