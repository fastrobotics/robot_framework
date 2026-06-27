/**
 * @file GlobalPathRequestMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <GeometryMsgs.hpp>

#include <vector>
using namespace fast::rf::messages;
namespace fast::rf::messages::NavMsgs {
/**
 * @brief Data Structure for encoding Global Path Request
 *
 */
struct GlobalPathRequest {
public:
  uint64_t path_uuid;          //!< Globally Unique Path ID
  GeometryMsgs::OdomMsg start; //!< Start Location with tolerance
  std::vector<GeometryMsgs::OdomMsg>
      pass_thru_points; //!< Optional ordered pass-thru points with tolerance
  GeometryMsgs::OdomMsg end; //!< End Location with tolerance
  GlobalPathRequest() : path_uuid(0) {}

  /**
   * @brief Validates if Request is valid
   *
   * @return true if Valid
   * @return false if Invalid Request
   */
  bool ok() {
    if (path_uuid == 0) {
      return false;
    }
    return true;
  }
};
} // namespace fast::rf::messages::NavMsgs
