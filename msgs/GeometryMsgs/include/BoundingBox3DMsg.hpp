/**
 * @file BoundingBox3DMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-10-18
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <PoseMsg.hpp>
#include <Vector3DMsg.hpp>
namespace fast::rf::messages::GeometryMsgs {
    /**
     * @brief A Bounding Box 3D Message
     *
     */
    struct BoundingBox3DMsg {
        PoseMsg center;
        fast::rf::messages::StandardMsgs::Vector3DMsg size;
        BoundingBox3DMsg() {}
        std::string pretty() {
            std::string str = "Bounding Box: Center: " + center.pretty() + " Size: " + size.pretty();
            return str;
        }
    };
}  // namespace fast::rf::messages::GeometryMsgs
