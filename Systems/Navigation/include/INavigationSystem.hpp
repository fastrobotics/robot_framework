/**
 * @file INavigationSystem.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

namespace fast::rf::NavigationSystem {
/**
 * @brief Interface for the Navigation System
 *
 */
class INavigationSystem {
public:
  INavigationSystem() = default;
  virtual ~INavigationSystem() = default;
};
} // namespace fast::rf::NavigationSystem