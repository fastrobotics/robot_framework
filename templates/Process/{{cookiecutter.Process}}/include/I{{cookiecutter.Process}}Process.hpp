/**
 * @file I{{cookiecutter.Process}}Process.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-Interface v0.1
 */
 
#pragma once
#include <IProcess.hpp>
#include <DiagnosticMsg.hpp>
#include <ReadyToArmStatusMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>

namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem::{{cookiecutter.Process}} {
/**
 * @brief Interface for the {{cookiecutter.Process}} fast::rf::Process
 *
 */
class I{{cookiecutter.Process}}Process: public IProcess {
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
  
};
} // namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem
