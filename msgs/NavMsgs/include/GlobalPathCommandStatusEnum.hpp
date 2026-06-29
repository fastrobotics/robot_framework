/**
 * @file GlobalPathCommandStatusEnum.hpp
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
enum class GlobalPathCommandStatusEnum {
    UNKNOWN = 0,     //!< Unknown
    STARTING = 1,    //!< Path Execution is Starting
    EXECUTING = 2,   //!< Path is being Executing, may be in this state for a while
    COMPLETED = 3,   //!< Path Execution has finished successfully
    FAILED = 4,      //!< Path Execution has failed
    END_OF_LIST = 5  //!< Not valid state, used for range checks of this enum

};
/**
 * @brief Convert status to string
 *
 * @param v
 * @return std::string
 */
std::string convert(GlobalPathCommandStatusEnum v) {
    switch (v) {
        case GlobalPathCommandStatusEnum::UNKNOWN:
            return "Unknown";
        case GlobalPathCommandStatusEnum::STARTING:
            return "Starting";
        case GlobalPathCommandStatusEnum::EXECUTING:
            return "Executing";
        case GlobalPathCommandStatusEnum::COMPLETED:
            return "Completed";
        case GlobalPathCommandStatusEnum::FAILED:
            return "Failed";
        default:
            return convert(GlobalPathCommandStatusEnum::UNKNOWN);
    }
    return "";
}
}  // namespace fast::rf::messages::NavMsgs
