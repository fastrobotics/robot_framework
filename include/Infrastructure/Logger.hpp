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

#include <DiagnosticMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
namespace fast::rf {
    /**
     * @brief Log a Diagnostic
     *
     */
#define logDiagnostic(diagnostic) getLoggerInstance().LOG_DIAGNOSTIC(__FILE__, __LINE__, diagnostic)
#define logDebug(tempstr) getLoggerInstance().LOG_DEBUG(__FILE__, __LINE__, tempstr)    //!< Log a Debug Message
#define logInfo(tempstr) getLoggerInstance().LOG_INFO(__FILE__, __LINE__, tempstr)      //!< Log a Info Message
#define logNotice(tempstr) getLoggerInstance().LOG_NOTICE(__FILE__, __LINE__, tempstr)  //!< Log a Notice Message
#define logWarn(tempstr) getLoggerInstance().LOG_WARN(__FILE__, __LINE__, tempstr)      //!< Log a Warn Message
#define logError(tempstr) getLoggerInstance().LOG_ERROR(__FILE__, __LINE__, tempstr)    //!< Log a Error Message
#define logFatal(tempstr) getLoggerInstance().LOG_FATAL(__FILE__, __LINE__, tempstr)    //!< Log a Fatal Message

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
            if (s_instance != nullptr) {
                return false;
            }
            s_instance = new Logger(level, name, true);
            if (s_instance->isLoggerOk() == false) {
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
            if (s_instance == nullptr) {
                s_instance = new Logger(Level::DEBUG, "default_logger", false);
            }
            return *s_instance;
        }
        /**
         * @brief Checks if Logger is ok
         *
         * @return true
         * @return false
         */
        bool isLoggerOk() { return m_loggerOk; }

        /**
         * @brief Do Not Use
         *
         * @param filename
         * @param linenumber
         * @param msg
         * @return LoggerStatus
         */
        // NOLINTNEXTLINE(readability-identifier-naming)
        LoggerStatus LOG_DIAGNOSTIC(std::string filename, uint64_t linenumber,
                                    fast::rf::messages::InfrastructureMsgs::DiagnosticMsg msg);

        /**
         * @brief Do Not Use
         *
         * @param filename
         * @param linenumber
         * @param tempstr
         * @return LoggerStatus
         */
        // NOLINTNEXTLINE(readability-identifier-naming)
        LoggerStatus LOG_DEBUG(std::string filename, uint64_t linenumber, std::string tempstr);

        /**
         * @brief Do Not Use
         *
         * @param filename
         * @param linenumber
         * @param tempstr
         * @return * LoggerStatus
         */
        // NOLINTNEXTLINE(readability-identifier-naming)
        LoggerStatus LOG_INFO(std::string filename, uint64_t linenumber, std::string tempstr);

        /**
         * @brief  Do Not Use
         *
         * @param filename
         * @param linenumber
         * @param tempstr
         * @return LoggerStatus
         */
        // NOLINTNEXTLINE(readability-identifier-naming)
        LoggerStatus LOG_NOTICE(std::string filename, uint64_t linenumber, std::string tempstr);

        /**
         * @brief  Do Not Use
         *
         * @param filename
         * @param linenumber
         * @param tempstr
         * @return LoggerStatus
         */
        // NOLINTNEXTLINE(readability-identifier-naming)
        LoggerStatus LOG_WARN(std::string filename, uint64_t linenumber, std::string tempstr);
        /**
         * @brief  Do Not Use
         *
         * @param filename
         * @param linenumber
         * @param tempstr
         * @return LoggerStatus
         */
        // NOLINTNEXTLINE(readability-identifier-naming)
        LoggerStatus LOG_ERROR(std::string filename, uint64_t linenumber, std::string tempstr);

        /**
         * @brief  Do Not Use
         *
         * @param filename
         * @param linenumber
         * @param tempstr
         * @return LoggerStatus
         */
        // NOLINTNEXTLINE(readability-identifier-naming)
        LoggerStatus LOG_FATAL(std::string filename, uint64_t linenumber, std::string tempstr);

        /**
         * @brief  Shutdown Logger.  Not typically required
         * @return void
         *
         */
        static void shutdown() {
            delete s_instance;
            s_instance = nullptr;
        }

       private:
        // Private Constructor
        Logger(Level level, std::string name, bool writeToFile);
        LoggerStatus printLog(std::string filename, uint64_t linenumber, Level level, std::string tempstr);

        const std::string GREEN_FOREGROUND = "\033[1;32m";
        const std::string YELLOW_FOREGROUND = "\033[1;33m";
        const std::string RED_FOREGROUND = "\033[1;31m";
        const std::string END_COLOR = "\033[0m";

        bool m_loggerOk{false};
        bool m_writeToFile{true};
        uint64_t m_lineCounter{0};
        Level m_verbosity{Level::DEBUG};
        std::ofstream m_logFile;
        std::string m_logName;
        char m_filePath[120];

        bool m_consolePrint{true};
        static Logger* s_instance;
    };

}  // namespace fast::rf