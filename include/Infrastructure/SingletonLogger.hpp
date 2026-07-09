#pragma once

#include <RobotFrameworkDefinitions.hpp>
#include <fstream>
#include <iostream>
#include <string>
namespace fast::rf {
#define log_debug(tempstr) getLoggerInstance().LOG_DEBUG(__FILE__, __LINE__, tempstr)
#define log_info(tempstr) getLoggerInstance().LOG_INFO(__FILE__, __LINE__, tempstr)
#define log_notice(tempstr) getLoggerInstance().LOG_NOTICE(__FILE__, __LINE__, tempstr)
#define log_warn(tempstr) getLoggerInstance().LOG_WARN(__FILE__, __LINE__, tempstr)
#define log_error(tempstr) getLoggerInstance().LOG_ERROR(__FILE__, __LINE__, tempstr)
#define log_fatal(tempstr) getLoggerInstance().LOG_FATAL(__FILE__, __LINE__, tempstr)

    class SingletonLogger {
       public:
        static constexpr uint16_t MAXLINE_COUNT = 5000;
        enum class LoggerStatus {
            UNKNOWN = 0,         //!< Uninitialized value.
            FAILED_TO_OPEN = 1,  //!< Logger was not able to open file to log.
            LOG_WRITTEN = 2,     //!< Log file was updated.
            LOG_SUPPRESSED = 3,  //!< Log entry was suppressed.
            END_OF_LIST = 4      //!< Last item of list. Used for Range Checks.
        };

        // Delete copy and move operations to enforce uniqueness
        SingletonLogger(const SingletonLogger&) = delete;
        SingletonLogger& operator=(const SingletonLogger&) = delete;
        SingletonLogger(SingletonLogger&&) = delete;
        SingletonLogger& operator=(SingletonLogger&&) = delete;

        // First Step: Creation and configuration step (Call once at app startup)
        static bool init(Level level, std::string name) {
            if (instance != nullptr) {
                throw std::runtime_error("Logger is already initialized!");
            }
            instance = new SingletonLogger(level, name);
            if (instance->logger_ok == false) {
                return false;
            }
            return true;
        }

        // Second Step: Global access step (Call anywhere else in your application)
        static SingletonLogger& getLoggerInstance() {
            if (instance == nullptr) {
                throw std::runtime_error("Logger has not been initialized yet!");
            }
            return *instance;
        }
        bool is_logger_ok() { return logger_ok; }
        LoggerStatus LOG_DEBUG(std::string filename, uint64_t linenumber, std::string tempstr);
        LoggerStatus LOG_INFO(std::string filename, uint64_t linenumber, std::string tempstr);
        LoggerStatus LOG_NOTICE(std::string filename, uint64_t linenumber, std::string tempstr);
        LoggerStatus LOG_WARN(std::string filename, uint64_t linenumber, std::string tempstr);
        LoggerStatus LOG_ERROR(std::string filename, uint64_t linenumber, std::string tempstr);
        LoggerStatus LOG_FATAL(std::string filename, uint64_t linenumber, std::string tempstr);

        // Optional: Manual cleanup helper for application shutdown
        static void shutdown() {
            delete instance;
            instance = nullptr;
        }

       private:
        // Private Constructor
        SingletonLogger(Level level, std::string name);

        const std::string GREEN_FOREGROUND = "\033[1;32m";
        const std::string YELLOW_FOREGROUND = "\033[1;33m";
        const std::string RED_FOREGROUND = "\033[1;31m";
        const std::string END_COLOR = "\033[0m";

        bool logger_ok{false};
        uint64_t line_counter{0};
        Level verbosity{Level::DEBUG};
        std::ofstream log_file;
        std::string log_name;
        char file_path[120];
        LoggerStatus print_log(std::string filename, uint64_t linenumber, Level level, std::string tempstr);
        bool console_print{true};

        // 1. Declare the static raw pointer (C++14 compatible syntax)
        static SingletonLogger* instance;
    };

}  // namespace fast::rf