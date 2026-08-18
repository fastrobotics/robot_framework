#pragma once
#include <AccelMsg.hpp>
#include <Covariance6DMsg.hpp>
#include <string>
namespace fast::rf::messages::GeometryMsgs {
    struct AccelWithCovarianceMsg {
        double time_stamp;
        AccelMsg accel;
        fast::rf::messages::StandardMsgs::Covariance6DMsg covariance;

        AccelWithCovarianceMsg() : time_stamp(-1.0) {}
        std::string pretty() {
            std::string str = "T: " + std::to_string(time_stamp) + "\n";
            str += accel.pretty();
            return str;
        }
    };
}  // namespace fast::rf::messages::GeometryMsgs
