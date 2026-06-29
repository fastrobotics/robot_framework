/**
 * @file GlobalPathPlanningStatusEnum.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <string>
namespace fast::rf::messages::NavMsgs {
/**
 * @brief Global Path Planning Status
 *
 */
enum class GlobalPathPlanningStatusEnum {
    UNKNOWN = 0,     //!< Unknown
    STARTING = 1,    //!< Path Planning is Starting
    PLANNING = 2,    //!< Path Planning is running, may be in this state for a while
    COMPLETED = 3,   //!< Path Planning has finished successfully
    FAILED = 4,      //!< Path Planning has failed
    END_OF_LIST = 5  //!< Not valid state, used for range checks of this enum

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
}  // namespace fast::rf::messages::NavMsgs
