/**
 * @file Base{{cookiecutter.Process}}Process.hpp
 * @author yDavid Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <I{{cookiecutter.Process}}Process.hpp>
namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem {
/**
 * @brief Base {{cookiecutter.Process}} Process
  @details Concrete {{cookiecutter.Process}} Processes should derive from this
 *
 */
class Base{{cookiecutter.Process}}Process : public I{{cookiecutter.Process}}Process {

public:
  /**
   * @brief Construct a new Base {{cookiecutter.Process}} Process object
   *
   */
  Base{{cookiecutter.Process}}Process() {}
  /**
   * @brief Update the base object
   *
   * @param current_time_sec
   * @param delta_time_sec
   * @return true If ok
   * @return false If not ok
   */
  bool base_update(double current_time_sec,
                   double delta_time_sec); //!< Base function to update

protected:
  double current_time_sec_{-1.0};    //!< Current system time
};
} // namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem