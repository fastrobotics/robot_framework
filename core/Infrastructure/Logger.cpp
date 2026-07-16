#include <Infrastructure/Logger.hpp>
#include <algorithm>

namespace fast::rf {

    Logger* Logger::instance = nullptr;
    Logger::Logger(Level level, std::string name, bool write_to_file) : write_to_file(write_to_file) {
        if ((level == Level::UNKNOWN) || (level == Level::END_OF_LIST)) {
            logger_ok = false;
            return;
        }
        verbosity = level;
        line_counter = 0;

        if (!name.empty() && name.at(0) == '/') {
            name.erase(name.begin());
        }
        std::replace(name.begin(), name.end(), '/', '_');
        log_name = name.empty() ? "default_logger" : name;
        if (write_to_file) {
            char buffer[100];
            sprintf(buffer, "%s.out", log_name.c_str());
            std::string home_dir = std::string(getenv("HOME"));
            sprintf(file_path, "%s/var/log/output/%s", home_dir.c_str(), buffer);
            std::ofstream log_file;
            log_file.open(file_path);  // Overwrite file.
            log_file.close();
        }
        logger_ok = true;
    }
    Logger::LoggerStatus Logger::LOG_DEBUG(std::string filename, uint64_t linenumber, std::string tempstr) {
        return print_log(filename, linenumber, Level::DEBUG, tempstr);
    }
    Logger::LoggerStatus Logger::LOG_INFO(std::string filename, uint64_t linenumber, std::string tempstr) {
        return print_log(filename, linenumber, Level::INFO, tempstr);
    }
    Logger::LoggerStatus Logger::LOG_NOTICE(std::string filename, uint64_t linenumber, std::string tempstr) {
        return print_log(filename, linenumber, Level::NOTICE, tempstr);
    }
    Logger::LoggerStatus Logger::LOG_WARN(std::string filename, uint64_t linenumber, std::string tempstr) {
        return print_log(filename, linenumber, Level::WARN, tempstr);
    }
    Logger::LoggerStatus Logger::LOG_ERROR(std::string filename, uint64_t linenumber, std::string tempstr) {
        return print_log(filename, linenumber, Level::ERROR, tempstr);
    }
    Logger::LoggerStatus Logger::LOG_FATAL(std::string filename, uint64_t linenumber, std::string tempstr) {
        return print_log(filename, linenumber, Level::FATAL, tempstr);
    }
    Logger::LoggerStatus Logger::print_log(std::string filename, uint64_t linenumber, Level level,
                                           std::string tempstr) {
        time_t rawtime;
        struct tm* timeinfo;
        char datebuffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(datebuffer, 80, "%d/%m/%Y %I:%M:%S", timeinfo);

        std::string str(datebuffer);
        if (write_to_file) {
            log_file.open(file_path, std::ios::out | std::ios::app | std::ios::binary | std::ios::ate);
        }

        std::string swcode_info = "";
        if (linenumber > 0) {
            swcode_info = filename + "(" + std::to_string(linenumber) + ")";
        }
        if (logger_ok == false) {
            printf("%s[%s %s]: ERROR: LOGGER HAS FAILED: %s%s\n", RED_FOREGROUND.c_str(), datebuffer, log_name.c_str(),
                   tempstr.c_str(), END_COLOR.c_str());
            return LoggerStatus::FAILED_TO_OPEN;
        }

        bool file_is_open = write_to_file && log_file.is_open();
        if (file_is_open || (!write_to_file && console_print)) {
            if (level >= verbosity) {
                line_counter++;
                switch (level) {
                    case Level::DEBUG:
                        if (file_is_open) {
                            log_file << "[" << datebuffer << "]: DEBUG: " << swcode_info << " " << tempstr << std::endl;
                        }
                        if (console_print) {
                            printf("[%s %s]: DEBUG: %s\n", datebuffer, log_name.c_str(), tempstr.c_str());
                        }
#ifdef ROS_INSTALLED
                        if (use_ROS_logger == true) {
                            ROS_DEBUG("%s", tempstr.c_str());
                        }
#endif
                        break;
                    case Level::INFO:
                        if (file_is_open) {
                            log_file << "[" << datebuffer << "]: INFO: " << swcode_info << " " << tempstr << std::endl;
                        }
                        if (console_print) {
                            printf("[%s %s]: INFO: %s\n", datebuffer, log_name.c_str(), tempstr.c_str());
                        }
#ifdef ROS_INSTALLED
                        if (use_ROS_logger == true) {
                            ROS_INFO("%s", tempstr.c_str());
                        }
#endif
                        break;
                    case Level::NOTICE:
                        if (file_is_open) {
                            log_file << "[" << datebuffer << "]: NOTICE: " << swcode_info << " " << tempstr
                                     << std::endl;
                        }
                        if (console_print) {
                            printf("%s[%s %s]: NOTICE: %s%s\n", GREEN_FOREGROUND.c_str(), datebuffer, log_name.c_str(),
                                   tempstr.c_str(), END_COLOR.c_str());
                        }
#ifdef ROS_INSTALLED
                        if (use_ROS_logger == true) {
                            ROS_INFO("%s", tempstr.c_str());
                        }
#endif
                        break;
                    case Level::WARN:
                        if (file_is_open) {
                            log_file << "[" << datebuffer << "]: WARN: " << swcode_info << " " << tempstr << std::endl;
                        }
                        if (console_print) {
                            printf("%s[%s %s]: WARN: %s%s\n", YELLOW_FOREGROUND.c_str(), datebuffer, log_name.c_str(),
                                   tempstr.c_str(), END_COLOR.c_str());
                        }
#ifdef ROS_INSTALLED
                        if (use_ROS_logger == true) {
                            ROS_WARN("%s", tempstr.c_str());
                        }
#endif
                        break;
                    case Level::ERROR:
                        if (file_is_open) {
                            log_file << "[" << datebuffer << "]: ERROR: " << swcode_info << " " << tempstr << std::endl;
                        }
                        if (console_print) {
                            printf("%s[%s %s]: ERROR: %s%s\n", RED_FOREGROUND.c_str(), datebuffer, log_name.c_str(),
                                   tempstr.c_str(), END_COLOR.c_str());
                        }
#ifdef ROS_INSTALLED
                        if (use_ROS_logger == true) {
                            ROS_ERROR("%s", tempstr.c_str());
                        }
#endif
                        break;
                    case Level::FATAL:
                        if (file_is_open) {
                            log_file << "[" << datebuffer << "]: FATAL: " << swcode_info << " " << tempstr << std::endl;
                        }
                        if (console_print) {
                            printf("%s[%s %s]: FATAL: %s%s\n", RED_FOREGROUND.c_str(), datebuffer, log_name.c_str(),
                                   tempstr.c_str(), END_COLOR.c_str());
                        }
#ifdef ROS_INSTALLED
                        if (use_ROS_logger == true) {
                            ROS_FATAL("%s", tempstr.c_str());
                        }
#endif
                        break;
                        /*default:
                            break;   Not possible to enter here, since this is a private function
                           and verbosity has already been validated. Keeping code here so it's
                           obvious.*/
                }
            } else {
                if (file_is_open) {
                    log_file.close();
                }
                return LoggerStatus::LOG_SUPPRESSED;
            }
        }
        if (file_is_open) {
            log_file.close();
        }
        if (write_to_file && line_counter > MAXLINE_COUNT) {
            log_file.open(file_path);  // Overwrite file.
            log_file.close();
            line_counter = 0;
        }
        return LoggerStatus::LOG_WRITTEN;
    }

}  // namespace fast::rf