/**
 * @compare_tag Process-BaseSource v0.1
 *
 */
#include <BaseLocalPoseFuserProcess.hpp>
#include <mutex>
namespace fast::rf::PoseSystem::LocalPoseSubsystem::LocalPoseFuser {
    bool BaseLocalPoseFuserProcess::init() { return true; }
    bool BaseLocalPoseFuserProcess::update(double currentTimeSec) {
        m_currentTimeSec = currentTimeSec;
        if (diagnosticManager.getDiagnostics(fast::rf::Level::ERROR).size() == 0) {
            ready_to_arm.ready_to_arm = true;
        } else {
            ready_to_arm.ready_to_arm = false;
        }

        return true;
    }
    std::string BaseLocalPoseFuserProcess::pretty() {
        std::string str = "\n---LocalPoseFuser---\n";
        str += "\tSys: " + std::string(fast::rf::PoseSystem::toString(fast::rf::PoseSystem::Id{})) + "/" +
               std::string(
                   fast::rf::PoseSystem::LocalPoseSubsystem::toString(fast::rf::PoseSystem::LocalPoseSubsystem::Id{})) +
               "/" +
               std::string(fast::rf::PoseSystem::LocalPoseSubsystem::LocalPoseFuser::toString(
                   fast::rf::PoseSystem::LocalPoseSubsystem::LocalPoseFuser::Id{})) +
               "\n";
        str += "\tT: " + std::to_string(m_currentTimeSec) + "\n";
        str += "\tReady To Arm: " + std::to_string(ready_to_arm.ready_to_arm) + "\n";
        str += diagnosticManager.pretty();
        str += "\tNew Data: " + std::to_string(is_new_local_pose) + "\n";
        str += local_pose_.pretty() + "\n";
        str += angular_acc_.pretty() + "\n";
        return str;
    }
    bool BaseLocalPoseFuserProcess::get_local_pose(
        fast::rf::messages::GeometryMsgs::OdomMsg& local_pose,
        fast::rf::messages::GeometryMsgs::AccelWithCovarianceMsg& angular_acc) {
        static std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);
        bool is_new = is_new_local_pose;
        local_pose = local_pose_;
        angular_acc = angular_acc_;
        is_new_local_pose = false;
        return is_new;
    }
    void BaseLocalPoseFuserProcess::new_local_pose(
        fast::rf::messages::GeometryMsgs::OdomMsg local_pose,
        fast::rf::messages::GeometryMsgs::AccelWithCovarianceMsg angular_acc) {
        local_pose_ = local_pose;
        angular_acc_ = angular_acc;
        is_new_local_pose = true;
    }
}  // namespace fast::rf::PoseSystem::LocalPoseSubsystem::LocalPoseFuser
