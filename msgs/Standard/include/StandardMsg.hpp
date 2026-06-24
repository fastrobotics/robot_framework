/**
 * @file StandardMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-24
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <vector>
/**
 * @brief Standard Message Namespace
 *
 */
namespace fast::rf::messages::Standard {
/**
 * @brief
 *
 */
struct Covariance6DMsg {
  /**
   * @brief 6D Covariance
    @details blah
   *
   */
  std::vector<double> covariance;
  Covariance6DMsg() { covariance.resize(36); }
};
} // namespace fast::rf::messages::Standard
