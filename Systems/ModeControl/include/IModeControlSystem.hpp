/**
 * @file IModeControlSystem.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

namespace fast::rf::ModeControlSystem {
/**
 * @brief Interface for the ModeControl System
 *
 */
class IModeControlSystem {
   public:
    IModeControlSystem() = default;
    virtual ~IModeControlSystem() = default;
};
}  // namespace fast::rf::ModeControlSystem