/**
 * @file TankDriveExecutorProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <BaseDriveExecutorProcess.hpp>
#include <IDriveExecutorOutput.hpp>

#include <TankDriveExecutorProcess/TankDriveExecutorOutput.hpp>

namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
/**
 * @brief Minimal implementation for a DriveExecutor Process
 *
 */
class TankDriveExecutorProcess : public BaseDriveExecutorProcess {
public:
  TankDriveExecutorProcess() : BaseDriveExecutorProcess() {}
  /**
   * @brief Update with recent timing data
   *
   * @param current_time_sec
   * @param delta_time_sec
   * @return true If update executed ok
   * @return false If update executed with some error
   */
  bool update(double current_time_sec, double delta_time_sec) override;

   virtual IDriveExecutorOutput *
  new_cmd(GeometryMsgs::TwistWithCovarianceMsg cmd) override;

private:
};
} // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem