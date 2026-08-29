/**
 * @file I{{cookiecutter.Process}}Process.hpp
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
#include <ReadyToArmStatusMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>

namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem::{{cookiecutter.Process}} {
/**
 * @brief Interface for the {{cookiecutter.Process}} Process
 *
 */
class I{{cookiecutter.Process}}Process {
public:
  I{{cookiecutter.Process}}Process() = default;
  virtual ~I{{cookiecutter.Process}}Process() = default;

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
   * @param currentTimeSec Current time stamp
   * @return true If the process updated ok
   * @return false If the process did not update ok
   */
  virtual bool update(double currentTimeSec) = 0;

  /**
   * @brief Pretty print the Process
   * 
   * @return std::string 
   */
  virtual std::string pretty() = 0;

  /**
         * @brief Get the diagnostic object
         *
         * @return fast::rf::messages::InfrastructureMsgs::DiagnosticMsg
         */
        virtual std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() = 0;

        /**
         * @brief Get the ready to arm object
         *
         * @return fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg
         */
  virtual fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg getReadyToArm() = 0;
        
  
};
} // namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem