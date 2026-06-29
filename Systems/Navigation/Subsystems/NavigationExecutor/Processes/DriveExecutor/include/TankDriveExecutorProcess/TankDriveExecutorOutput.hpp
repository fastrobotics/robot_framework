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

#include <stdint.h>

#include <IDriveExecutorOutput.hpp>

namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem {

struct TankDriveExecutorOutput : public IDriveExecutorOutput {
    TankDriveExecutorOutput() : IDriveExecutorOutput() {}
    double left_drive{0};   //!< Left Drive Output
    double right_drive{0};  //!< Right Drive Output

   private:
};
}  // namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem