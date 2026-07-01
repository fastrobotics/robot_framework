#include <DummyPoseSystem/DummyPoseSystem.hpp>
namespace fast::rf::PoseSystem {
bool DummyPoseSystem::update(double current_time_sec, [[maybe_unused]] double delta_time_sec) {
    bool status = BasePoseSystem::base_update(current_time_sec, delta_time_sec);
    if (status == false) {
        return false;
    }

    global_pose_.time_stamp = current_time_sec_;
    local_pose_.time_stamp = current_time_sec_;
    return true;
}
}  // namespace fast::rf::PoseSystem