/**
 * @file IDataStorageSystem.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

namespace fast::rf::DataStorageSystem {
/**
 * @brief Interface for the DataStorage System
 *
 */
class IDataStorageSystem {
public:
  IDataStorageSystem() = default;
  virtual ~IDataStorageSystem() = default;
};
} // namespace fast::rf::DataStorageSystem