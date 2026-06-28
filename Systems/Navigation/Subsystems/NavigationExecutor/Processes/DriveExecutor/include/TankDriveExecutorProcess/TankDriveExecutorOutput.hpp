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

namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {
class TankDriveExecutorOutput : public IDriveExecutorOutput {
public:
  TankDriveExecutorOutput() : IDriveExecutorOutput() {}

private:
};
} // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem