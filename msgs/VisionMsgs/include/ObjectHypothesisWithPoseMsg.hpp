/**
 * @file ObjectHypothesisWithPoseMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-10-18
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <PoseWithCovarianceMsg.hpp>
namespace fast::rf::messages::VisionMsgs {
    /**
     * @brief Data about a potential Object
     *
     */
    struct ObjectHypothesisWithPoseMsg {
        std::string classification_id{""};  //!< The Object Classification
        double score;  //!< A score for the object, as a percentage. <=0% is unknown/invalid, 100% is perfectly known.
                       //!< Anything above 100% is invalid
        fast::rf::messages::GeometryMsgs::PoseWithCovarianceMsg pose;  //!< Object Pose
        bool isOk() {
            if (score <= 0.0) {
                return false;
            }
            if (score > 100.0) {
                return false;
            }
            return true;
        }
        ObjectHypothesisWithPoseMsg() : score(-1.0) {}
        std::string pretty() {
            std::string str = "Object Hypothesis: Class: " + classification_id + " Score: " + std::to_string(score) +
                              " Valid: " + std::to_string(isOk()) + " " + pose.pose.pretty();
            return str;
        }
    };
}  // namespace fast::rf::messages::VisionMsgs
