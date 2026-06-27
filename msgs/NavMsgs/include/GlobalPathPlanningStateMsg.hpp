/**
 * @file GlobalPathPlanningStateMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <GlobalPathPlanningStatusEnum.hpp>
#include <cstdint>
#include <vector>
using namespace fast::rf::messages;

namespace fast::rf::messages::NavMsgs {
/**
 * @brief Data Structure for encoding Global Path Planning State
 *
 */
struct GlobalPathPlanningStateMsg {
public:
  uint64_t path_uuid; //!< Globally Unique Path ID, should match the Request ID
  GlobalPathPlanningStatusEnum state; //!< The state of the planning request
  GlobalPathPlanningStateMsg()
      : path_uuid(0), state(GlobalPathPlanningStatusEnum::UNKNOWN) {}
};
} // namespace fast::rf::messages::NavMsgs
