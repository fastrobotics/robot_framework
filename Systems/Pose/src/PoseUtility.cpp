#include <PoseUtility.hpp>
namespace fast::rf::PoseSystem {
    bool PoseUtility::differentiate(fast::rf::messages::GeometryMsgs::OdomMsg previous,
                                    fast::rf::messages::GeometryMsgs::OdomMsg current,
                                    fast::rf::messages::GeometryMsgs::AccelMsg& computed_angular_acc) {
        double delta_t = current.time_stamp - previous.time_stamp;
        computed_angular_acc.angular.x = (current.twist.twist.angular.x - previous.twist.twist.angular.x) / (delta_t);
        computed_angular_acc.angular.y = (current.twist.twist.angular.y - previous.twist.twist.angular.y) / (delta_t);
        computed_angular_acc.angular.z = (current.twist.twist.angular.z - previous.twist.twist.angular.z) / (delta_t);
        computed_angular_acc.linear.x = (current.twist.twist.linear.x - previous.twist.twist.linear.x) / (delta_t);
        computed_angular_acc.linear.y = (current.twist.twist.linear.y - previous.twist.twist.linear.y) / (delta_t);
        computed_angular_acc.linear.z = (current.twist.twist.linear.z - previous.twist.twist.linear.z) / (delta_t);
        return true;
    }
}  // namespace fast::rf::PoseSystem