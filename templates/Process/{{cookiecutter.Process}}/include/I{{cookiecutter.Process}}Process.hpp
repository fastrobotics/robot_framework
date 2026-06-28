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
namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem {
/**
 * @brief Interface for the {{cookiecutter.Process}} Process
 *
 */
class I{{cookiecutter.Process}}Process {
public:
  I{{cookiecutter.Process}}Process() = default;
  virtual ~I{{cookiecutter.Process}}Process() = default;
  /**
   * @brief Generic Update function
   *
   * @param current_time_sec Current time stamp
   * @param delta_time_sec Difference in time between previous iterations
   * @return true If the process updated ok
   * @return false If the process did not update ok
   */
  virtual bool update(double current_time_sec, double delta_time_sec) = 0;
  
};
} // namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem