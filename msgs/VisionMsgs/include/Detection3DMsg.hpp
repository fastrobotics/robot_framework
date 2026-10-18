/**
 * @file Detection3DMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-10-18
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <BoundingBox3DMsg.hpp>
#include <ObjectHypothesisWithPoseMsg.hpp>
#include <PointCloudMsg.hpp>
#include <vector>
namespace fast::rf::messages::VisionMsgs {
    /**
     * @brief A message about a 3D Detection
     *
     */
    struct Detection3DMsg {
        double time_stamp;                                           //!< Timestamp of message
        std::vector<ObjectHypothesisWithPoseMsg> results;            //!< Potential Objects in a Point Cloud
        fast::rf::messages::GeometryMsgs::BoundingBox3DMsg bbox;     //!< Boundary box of the Point Cloud
        fast::rf::messages::SensorMsgs::PointCloudMsg source_cloud;  //!< Point Cloud
        Detection3DMsg() {}
        std::string pretty() {
            std::string str = "3D Detection: T: " + std::to_string(time_stamp) + "\n";
            str += "\tResult Count: " + std::to_string(results.size()) + "\n";
            uint64_t counter = 0;
            for (auto result : results) {
                str += "\t[" + std::to_string(counter) + "/" + std::to_string(results.size()) + "] " + result.pretty() +
                       "\n";
                counter++;
            }
            str += "\t" + bbox.pretty();

            return str;
        }
    };
}  // namespace fast::rf::messages::VisionMsgs
