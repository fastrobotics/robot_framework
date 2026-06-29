/**
 * @file ICommsSystem.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

namespace fast::rf::CommsSystem {
/**
 * @brief Interface for the Comms System
 *
 */
class ICommsSystem {
   public:
    ICommsSystem() = default;
    virtual ~ICommsSystem() = default;
};
}  // namespace fast::rf::CommsSystem