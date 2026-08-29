#include <Infrastructure/Logger.hpp>
#include <algorithm>

namespace fast::rf {

    Logger* Logger::s_instance = nullptr;
    Logger::Logger(Level level, std::string name, bool writeToFile) : m_writeToFile(writeToFile) {
        if ((level == Level::UNKNOWN) || (level == Level::END_OF_LIST)) {
            m_loggerOk = false;
            return;
        }
        m_verbosity = level;
        m_lineCounter = 0;

        if (!name.empty() && name.at(0) == '/') {
            name.erase(name.begin());
        }
        std::replace(name.begin(), name.end(), '/', '_');
        m_logName = name.empty() ? "default_logger" : name;
        if (writeToFile) {
            char buffer[100];
            sprintf(buffer, "%s.out", m_logName.c_str());
            std::string home_dir = std::string(getenv("HOME"));
            sprintf(m_filePath, "%s/var/log/output/%s", home_dir.c_str(), buffer);
            std::ofstream log_file;
            log_file.open(m_filePath);  // Overwrite file.
            log_file.close();
        }
        m_loggerOk = true;
    }
    Logger::LoggerStatus Logger::LOG_DIAGNOSTIC(std::string filename, uint64_t linenumber,
                                                fast::rf::messages::InfrastructureMsgs::DiagnosticMsg msg) {
        std::string diag_string = msg.pretty();
        switch (msg.level) {
            case fast::rf::Level::NOERROR:
                return LOG_INFO(filename, linenumber, diag_string);
            case fast::rf::Level::DEBUG:
                return LOG_DEBUG(filename, linenumber, diag_string);
            case fast::rf::Level::INFO:
                return LOG_INFO(filename, linenumber, diag_string);
            case fast::rf::Level::NOTICE:
                return LOG_NOTICE(filename, linenumber, diag_string);
            case fast::rf::Level::WARN:
                return LOG_WARN(filename, linenumber, diag_string);
            case fast::rf::Level::ERROR:
                return LOG_ERROR(filename, linenumber, diag_string);
            case fast::rf::Level::FATAL:
                return LOG_FATAL(filename, linenumber, diag_string);

            default:
                return LOG_ERROR("", 0, "UNKNOWN LEVEL: " + std::to_string((uint8_t)msg.level));
        }
        return LoggerStatus::FAILED_TO_OPEN;
    }
    Logger::LoggerStatus Logger::LOG_DEBUG(std::string filename, uint64_t linenumber, std::string tempstr) {
        return printLog(filename, linenumber, Level::DEBUG, tempstr);
    }
    Logger::LoggerStatus Logger::LOG_INFO(std::string filename, uint64_t linenumber, std::string tempstr) {
        return printLog(filename, linenumber, Level::INFO, tempstr);
    }
    Logger::LoggerStatus Logger::LOG_NOTICE(std::string filename, uint64_t linenumber, std::string tempstr) {
        return printLog(filename, linenumber, Level::NOTICE, tempstr);
    }
    Logger::LoggerStatus Logger::LOG_WARN(std::string filename, uint64_t linenumber, std::string tempstr) {
        return printLog(filename, linenumber, Level::WARN, tempstr);
    }
    Logger::LoggerStatus Logger::LOG_ERROR(std::string filename, uint64_t linenumber, std::string tempstr) {
        return printLog(filename, linenumber, Level::ERROR, tempstr);
    }
    Logger::LoggerStatus Logger::LOG_FATAL(std::string filename, uint64_t linenumber, std::string tempstr) {
        return printLog(filename, linenumber, Level::FATAL, tempstr);
    }
    Logger::LoggerStatus Logger::printLog(std::string filename, uint64_t linenumber, Level level, std::string tempstr) {
        time_t rawtime;
        struct tm* timeinfo;
        char datebuffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(datebuffer, 80, "%d/%m/%Y %I:%M:%S", timeinfo);

        std::string str(datebuffer);
        if (m_writeToFile) {
            m_logFile.open(m_filePath, std::ios::out | std::ios::app | std::ios::binary | std::ios::ate);
        }

        std::string swCodeInfo = "";
        if (linenumber > 0) {
            swCodeInfo = filename + "(" + std::to_string(linenumber) + ")";
        }
        if (m_loggerOk == false) {
            printf("%s[%s %s]: ERROR: LOGGER HAS FAILED: %s%s\n", RED_FOREGROUND.c_str(), datebuffer, m_logName.c_str(),
                   tempstr.c_str(), END_COLOR.c_str());
            return LoggerStatus::FAILED_TO_OPEN;
        }

        bool fileIsOpen = m_writeToFile && m_logFile.is_open();
        if (fileIsOpen || (!m_writeToFile && m_consolePrint)) {
            if (level >= m_verbosity) {
                m_lineCounter++;
                switch (level) {
                    case Level::DEBUG:
                        if (fileIsOpen) {
                            m_logFile << "[" << datebuffer << "]: DEBUG: " << swCodeInfo << " " << tempstr << std::endl;
                        }
                        if (m_logFile) {
                            printf("[%s %s]: DEBUG: %s\n", datebuffer, m_logName.c_str(), tempstr.c_str());
                        }
#ifdef ROS_INSTALLED
                        if (use_ROS_logger == true) {
                            ROS_DEBUG("%s", tempstr.c_str());
                        }
#endif
                        break;
                    case Level::INFO:
                        if (fileIsOpen) {
                            m_logFile << "[" << datebuffer << "]: INFO: " << swCodeInfo << " " << tempstr << std::endl;
                        }
                        if (m_consolePrint) {
                            printf("[%s %s]: INFO: %s\n", datebuffer, m_logName.c_str(), tempstr.c_str());
                        }
#ifdef ROS_INSTALLED
                        if (use_ROS_logger == true) {
                            ROS_INFO("%s", tempstr.c_str());
                        }
#endif
                        break;
                    case Level::NOTICE:
                        if (fileIsOpen) {
                            m_logFile << "[" << datebuffer << "]: NOTICE: " << swCodeInfo << " " << tempstr
                                      << std::endl;
                        }
                        if (m_consolePrint) {
                            printf("%s[%s %s]: NOTICE: %s%s\n", GREEN_FOREGROUND.c_str(), datebuffer, m_logName.c_str(),
                                   tempstr.c_str(), END_COLOR.c_str());
                        }
#ifdef ROS_INSTALLED
                        if (use_ROS_logger == true) {
                            ROS_INFO("%s", tempstr.c_str());
                        }
#endif
                        break;
                    case Level::WARN:
                        if (fileIsOpen) {
                            m_logFile << "[" << datebuffer << "]: WARN: " << swCodeInfo << " " << tempstr << std::endl;
                        }
                        if (m_consolePrint) {
                            printf("%s[%s %s]: WARN: %s%s\n", YELLOW_FOREGROUND.c_str(), datebuffer, m_logName.c_str(),
                                   tempstr.c_str(), END_COLOR.c_str());
                        }
#ifdef ROS_INSTALLED
                        if (use_ROS_logger == true) {
                            ROS_WARN("%s", tempstr.c_str());
                        }
#endif
                        break;
                    case Level::ERROR:
                        if (fileIsOpen) {
                            m_logFile << "[" << datebuffer << "]: ERROR: " << swCodeInfo << " " << tempstr << std::endl;
                        }
                        if (m_consolePrint) {
                            printf("%s[%s %s]: ERROR: %s%s\n", RED_FOREGROUND.c_str(), datebuffer, m_logName.c_str(),
                                   tempstr.c_str(), END_COLOR.c_str());
                        }
#ifdef ROS_INSTALLED
                        if (use_ROS_logger == true) {
                            ROS_ERROR("%s", tempstr.c_str());
                        }
#endif
                        break;
                    case Level::FATAL:
                        if (fileIsOpen) {
                            m_logFile << "[" << datebuffer << "]: FATAL: " << swCodeInfo << " " << tempstr << std::endl;
                        }
                        if (m_consolePrint) {
                            printf("%s[%s %s]: FATAL: %s%s\n", RED_FOREGROUND.c_str(), datebuffer, m_logName.c_str(),
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
                           and m_verbosity has already been validated. Keeping code here so it's
                           obvious.*/
                }
            } else {
                if (fileIsOpen) {
                    m_logFile.close();
                }
                return LoggerStatus::LOG_SUPPRESSED;
            }
        }
        if (fileIsOpen) {
            m_logFile.close();
        }
        if (m_writeToFile && m_lineCounter > MAXLINE_COUNT) {
            m_logFile.open(m_filePath);  // Overwrite file.
            m_logFile.close();
            m_lineCounter = 0;
        }
        return LoggerStatus::LOG_WRITTEN;
    }

}  // namespace fast::rf