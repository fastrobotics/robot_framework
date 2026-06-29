/**
 * @file GlobalPathCommandMsg.hpp
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
#include <cstdint>
#include <vector>
using namespace fast::rf::messages;
namespace fast::rf::messages::NavMsgs {
/**
 * @brief Data Structure for Encoding Global Path Command
 *
 */
struct GlobalPathCommandMsg {
    uint64_t path_uuid;                              //!< Global Unique Path ID
    GeometryMsgs::OdomMsg start;                     //!< Start coordinate.  Covariance indicates how
                                                     //!< close robot must be to start the path.
    std::vector<GeometryMsgs::OdomMsg> path_points;  //!<  Each point indicates how close it must be to be
                                                     //!<  reached.  Start and End are specifically excluded from
                                                     //!<  this list.
    GeometryMsgs::OdomMsg end;                       //!< End coordinate.  Covariance indicates close
                                                     //!< robot must be to finish the path.
    GlobalPathCommandMsg() : path_uuid(0) {}

    /**
     * @brief Validates if Path Command is ok
     *
     * @return true if Ok
     * @return false if Not Ok
     */
    bool ok() {
        if (path_uuid == 0) {
            return false;
        }
        return true;
    }
};
}  // namespace fast::rf::messages::NavMsgs
