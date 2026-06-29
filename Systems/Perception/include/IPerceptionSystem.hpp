/**
 * @file IPerceptionSystem.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

namespace fast::rf::PerceptionSystem {
/**
 * @brief Interface for the Perception System
 *
 */
class IPerceptionSystem {
   public:
    IPerceptionSystem() = default;
    virtual ~IPerceptionSystem() = default;
};
}  // namespace fast::rf::PerceptionSystem