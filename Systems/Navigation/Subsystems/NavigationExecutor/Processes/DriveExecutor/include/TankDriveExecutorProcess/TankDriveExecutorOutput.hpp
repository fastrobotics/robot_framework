/**
 * @file TankDriveExecutorOutput.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <IDriveExecutorOutput.hpp>
#include <stdint.h>

namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
struct TankDriveExecutorOutput : public IDriveExecutorOutput {
  TankDriveExecutorOutput() : IDriveExecutorOutput() {}
  uint16_t left_drive{0};
  uint16_t right_drive{0};

private:
};
} // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem