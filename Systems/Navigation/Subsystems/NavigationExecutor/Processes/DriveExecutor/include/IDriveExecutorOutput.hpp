/**
 * @file IDriveExecutorOutput.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
/**
 * @brief Interface for the DriveExecutor Process
 *
 */
struct IDriveExecutorOutput {
  IDriveExecutorOutput() = default;
  virtual ~IDriveExecutorOutput() = default;
};
} // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem