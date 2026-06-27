/**
 * @file GlobalPathCommandStateMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <GlobalPathCommandStatusEnum.hpp>
#include <cstdint>

namespace fast::rf::messages::NavMsgs {
/**
 * @brief Data Structure for encoding Global Path Command State
 *
 */
struct GlobalPathCommandStateMsg {
  uint64_t path_uuid;                //!< Globally unique Path ID
  GlobalPathCommandStatusEnum state; //!< State of the Path
  GlobalPathCommandStateMsg()
      : path_uuid(0), state(GlobalPathCommandStatusEnum::UNKNOWN) {}
};
} // namespace fast::rf::messages::NavMsgs
