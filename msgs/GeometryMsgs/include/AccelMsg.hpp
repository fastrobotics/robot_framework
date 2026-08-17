#pragma once
#include <Vector3DMsg.hpp>
#include <string>
namespace fast::rf::messages::GeometryMsgs {
    struct AccelMsg {
        fast::rf::messages::StandardMsgs::Vector3DMsg linear;
        fast::rf::messages::StandardMsgs::Vector3DMsg angular;
        AccelMsg() {}
        std::string pretty() {
            std::string str = "Linear: " + linear.pretty() + "\n";
            str += "Angular: " + angular.pretty();
            return str;
        }
    };
}  // namespace fast::rf::messages::GeometryMsgs
