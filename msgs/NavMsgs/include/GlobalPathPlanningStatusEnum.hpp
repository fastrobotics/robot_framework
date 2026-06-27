#pragma once
#include <string>
namespace fast::rf::messages::NavMsgs {
/**
 * @brief Global Path Planning Status
 *
 */
enum class GlobalPathPlanningStatusEnum {
  UNKNOWN = 0,
  STARTING = 1,
  PLANNING = 2,
  COMPLETED = 3,
  FAILED = 4,
  END_OF_LIST = 5

};
/**
 * @brief Convert status to string
 *
 * @param v
 * @return std::string
 */
std::string convert(GlobalPathPlanningStatusEnum v) {
  switch (v) {
    case GlobalPathPlanningStatusEnum::UNKNOWN:
      return "Unknown";
    case GlobalPathPlanningStatusEnum::STARTING:
      return "Starting";
    case GlobalPathPlanningStatusEnum::PLANNING:
      return "Planning";
    case GlobalPathPlanningStatusEnum::COMPLETED:
      return "Completed";
    case GlobalPathPlanningStatusEnum::FAILED:
      return "Failed";
    default:
      return convert(GlobalPathPlanningStatusEnum::UNKNOWN);
  }
  return "";
}
} // namespace fast::rf::messages::NavMsgs
