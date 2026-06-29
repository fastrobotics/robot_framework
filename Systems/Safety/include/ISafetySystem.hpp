/**
 * @file ISafetySystem.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

namespace fast::rf::SafetySystem {
/**
 * @brief Interface for the Safety System
 *
 */
class ISafetySystem {
   public:
    ISafetySystem() = default;
    virtual ~ISafetySystem() = default;
};
}  // namespace fast::rf::SafetySystem