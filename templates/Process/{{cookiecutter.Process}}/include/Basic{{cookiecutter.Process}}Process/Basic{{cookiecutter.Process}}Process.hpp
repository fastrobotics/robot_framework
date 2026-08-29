/**
 * @file Basic{{cookiecutter.Process}}Process.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <Base{{cookiecutter.Process}}Process.hpp>

namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem::{{cookiecutter.Process}} {

class Basic{{cookiecutter.Process}}ProcessConfig {
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
}
/**
 * @brief Minimal Implementation for a {{cookiecutter.Process}} Process
 *
 */
class Basic{{cookiecutter.Process}}Process : public Base{{cookiecutter.Process}}Process {
public:
  
  Basic{{cookiecutter.Process}}Process() : Base{{cookiecutter.Process}}Process() {}

   /**
         * @brief Initialize the Object
         *
         * @return true
         * @return false
         */
        bool init() override;

     bool setConfig(Basic{{cookiecutter.Process}}ProcessConfig config) {
            if(config.isOk() == false) {
                  fast::rf::Logger::log_error("Unable to set Config! " + config.pretty());
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

  /**
   * @brief Human readable status of object
   * 
   * @return std::string 
   */
   std::string pretty() override;

private:
  Basic{{cookiecutter.Process}}ProcessConfig m_config;
};
} // namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem