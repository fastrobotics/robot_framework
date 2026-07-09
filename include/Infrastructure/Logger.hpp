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
#include <string>
namespace fast::rf {
//! Log a Debug Line
/*!
  \param tempstr The string to output.
*/
#define log_debug(tempstr) LOG_DEBUG(__FILE__, __LINE__, tempstr)

#define log_warn(tempstr) LOG_WARN(__FILE__, __LINE__, tempstr)

    class Logger {
       public:
        static constexpr uint16_t MAXLINE_COUNT = 5000;
        enum class LoggerStatus {
            UNKNOWN = 0,         //!< Uninitialized value.
            FAILED_TO_OPEN = 1,  //!< Logger was not able to open file to log.
            LOG_WRITTEN = 2,     //!< Log file was updated.
            LOG_SUPPRESSED = 3,  //!< Log entry was suppressed.
            END_OF_LIST = 4      //!< Last item of list. Used for Range Checks.
        };
        Logger() = default;
        virtual ~Logger() = default;
        Logger(Level level, std::string name);
        // bool set_log_verbosity(Level level);

        //! Log a Debug Line.  Do not use, use: log_debug
        LoggerStatus LOG_DEBUG(std::string filename, uint64_t linenumber, std::string tempstr);
        LoggerStatus LOG_WARN(std::string filename, uint64_t linenumber, std::string tempstr);

        bool is_logger_ok() { return logger_ok; }

       private:
        const std::string GREEN_FOREGROUND = "\033[1;32m";
        const std::string YELLOW_FOREGROUND = "\033[1;33m";
        const std::string RED_FOREGROUND = "\033[1;31m";
        const std::string END_COLOR = "\033[0m";

        bool logger_ok{false};
        uint64_t line_counter{0};
        Level verbosity{Level::DEBUG};
        std::ofstream log_file;
        std::string node_name;
        char file_path[120];
        LoggerStatus print_log(std::string filename, uint64_t linenumber, Level level, std::string tempstr);
        bool console_print{true};
    };
}  // namespace fast::rf