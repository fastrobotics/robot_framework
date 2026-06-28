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

namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem {
/**
 * @brief Minimal implementation for a {{cookiecutter.Process}} Process
 *
 */
class Basic{{cookiecutter.Process}}Process : public Base{{cookiecutter.Process}}Process {
public:
  Basic{{cookiecutter.Process}}Process() : Base{{cookiecutter.Process}}Process() {}
  /**
   * @brief Update with recent timing data
   *
   * @param current_time_sec
   * @param delta_time_sec
   * @return true If update executed ok
   * @return false If update executed with some error
   */
  bool update(double current_time_sec, double delta_time_sec) override;

private:
};
} // namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem