/**
 * @file GlobalPathResponseMsg.hpp
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
#include <GlobalPathPlanningStatusEnum.hpp>
#include <vector>
using namespace fast::rf::messages;
namespace fast::rf::messages::NavMsgs {
/**
 * @brief Data Structure encoding a response from a Global Path Request
 *
 */
struct GlobalPathResponse {
public:
  uint64_t path_uuid; //!< Globally Unique Path ID, should match the Request ID
  GlobalPathPlanningStatusEnum state; //!< The state of the planning request
  std::vector<GeometryMsgs::OdomMsg>
      path_points; //!< Path Points.  Should only be used if state was
                   //!< Completed.
  GlobalPathResponse()
      : path_uuid(0), state(GlobalPathPlanningStatusEnum::UNKNOWN) {}
};
} // namespace fast::rf::messages::NavMsgs
