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
#include <cstdint>
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
  static inline constexpr uint16_t DIMENSION = 6;
  std::vector<double> covariance;
  Covariance6DMsg() { covariance.resize(DIMENSION * DIMENSION); }
};
} // namespace fast::rf::messages::Standard
