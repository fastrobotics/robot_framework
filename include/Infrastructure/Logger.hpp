/**
 * @file Logger.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-09
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <RobotFrameworkDefinitions.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
namespace fast::rf {
#define log_debug(tempstr) getLoggerInstance().LOG_DEBUG(__FILE__, __LINE__, tempstr)    //!< Log a Debug Message
#define log_info(tempstr) getLoggerInstance().LOG_INFO(__FILE__, __LINE__, tempstr)      //!< Log a Info Message
#define log_notice(tempstr) getLoggerInstance().LOG_NOTICE(__FILE__, __LINE__, tempstr)  //!< Log a Notice Message
#define log_warn(tempstr) getLoggerInstance().LOG_WARN(__FILE__, __LINE__, tempstr)      //!< Log a Warn Message
#define log_error(tempstr) getLoggerInstance().LOG_ERROR(__FILE__, __LINE__, tempstr)    //!< Log a Error Message
#define log_fatal(tempstr) getLoggerInstance().LOG_FATAL(__FILE__, __LINE__, tempstr)    //!< Log a Fatal Message

    /**
     * @brief Logger Class
     *
     */
    class Logger {
       public:
        static constexpr uint16_t MAXLINE_COUNT =
            5000;  //!< Amount of data to write to file, before the file is restarted
        /**
         * @brief Status Enum of Logger
         *
         */
        enum class LoggerStatus {
            UNKNOWN = 0,         //!< Uninitialized value.
            FAILED_TO_OPEN = 1,  //!< Logger was not able to open file to log.
            LOG_WRITTEN = 2,     //!< Log file was updated.
            LOG_SUPPRESSED = 3,  //!< Log entry was suppressed.
            END_OF_LIST = 4      //!< Last item of list. Used for Range Checks.
        };

        // Delete copy and move operations to enforce uniqueness
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger(Logger&&) = delete;
        Logger& operator=(Logger&&) = delete;

        /**
         * @brief Initialize Logger
         *
         * @param level
         * @param name
         * @return true
         * @return false
         */
        static bool init(Level level, std::string name) {
            if (instance != nullptr) {
                throw std::runtime_error("Logger is already initialized!");
            }
            instance = new Logger(level, name, true);
            if (instance->logger_ok == false) {
                return false;
            }
            return true;
        }

        /**
         * @brief Get the Logger Instance object.  Not typically required to be used.
         *
         * @return Logger&
         */
        static Logger& getLoggerInstance() {
            if (instance == nullptr) {
                instance = new Logger(Level::DEBUG, "default_logger", false);
            }
            return *instance;
        }
        /**
         * @brief Checks if Logger is ok
         *
         * @return true
         * @return false
         */
        bool is_logger_ok() { return logger_ok; }

        /**
         * @brief Do Not Use
         *
         * @param filename
         * @param linenumber
         * @param tempstr
         * @return LoggerStatus
         */
        LoggerStatus LOG_DEBUG(std::string filename, uint64_t linenumber, std::string tempstr);

        /**
         * @brief Do Not Use
         *
         * @param filename
         * @param linenumber
         * @param tempstr
         * @return * LoggerStatus
         */
        LoggerStatus LOG_INFO(std::string filename, uint64_t linenumber, std::string tempstr);

        /**
         * @brief  Do Not Use
         *
         * @param filename
         * @param linenumber
         * @param tempstr
         * @return LoggerStatus
         */
        LoggerStatus LOG_NOTICE(std::string filename, uint64_t linenumber, std::string tempstr);

        /**
         * @brief  Do Not Use
         *
         * @param filename
         * @param linenumber
         * @param tempstr
         * @return LoggerStatus
         */
        LoggerStatus LOG_WARN(std::string filename, uint64_t linenumber, std::string tempstr);
        /**
         * @brief  Do Not Use
         *
         * @param filename
         * @param linenumber
         * @param tempstr
         * @return LoggerStatus
         */
        LoggerStatus LOG_ERROR(std::string filename, uint64_t linenumber, std::string tempstr);

        /**
         * @brief  Do Not Use
         *
         * @param filename
         * @param linenumber
         * @param tempstr
         * @return LoggerStatus
         */
        LoggerStatus LOG_FATAL(std::string filename, uint64_t linenumber, std::string tempstr);

        /**
         * @brief  Shutdown Logger.  Not typically required
         * @return void
         *
         */
        static void shutdown() {
            delete instance;
            instance = nullptr;
        }

       private:
        // Private Constructor
        Logger(Level level, std::string name, bool write_to_file);

        const std::string GREEN_FOREGROUND = "\033[1;32m";
        const std::string YELLOW_FOREGROUND = "\033[1;33m";
        const std::string RED_FOREGROUND = "\033[1;31m";
        const std::string END_COLOR = "\033[0m";

        bool logger_ok{false};
        bool write_to_file{true};
        uint64_t line_counter{0};
        Level verbosity{Level::DEBUG};
        std::ofstream log_file;
        std::string log_name;
        char file_path[120];
        LoggerStatus print_log(std::string filename, uint64_t linenumber, Level level, std::string tempstr);
        bool console_print{true};

        // 1. Declare the static raw pointer (C++14 compatible syntax)
        static Logger* instance;
    };

}  // namespace fast::rf