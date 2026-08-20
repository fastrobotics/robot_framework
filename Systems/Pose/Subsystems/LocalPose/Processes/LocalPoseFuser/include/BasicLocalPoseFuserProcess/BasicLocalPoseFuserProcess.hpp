/**
 * @file BasicLocalPoseFuserProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <BaseLocalPoseFuserProcess.hpp>

namespace fast::rf::PoseSystem::LocalPoseSubsystem::LocalPoseFuser {
    /**
     * @brief Minimal Implementation for a LocalPoseFuser Process
     *
     */
    class BasicLocalPoseFuserProcess : public BaseLocalPoseFuserProcess {
       public:
        BasicLocalPoseFuserProcess() : BaseLocalPoseFuserProcess() {}

        /**
         * @brief Initialize the Object
         *
         * @return true
         * @return false
         */
        bool init() override;

        /**
         * @brief Update with recent timing data
         *
         * @param current_time_sec
         * @return true If update executed ok
         * @return false If update executed with some error
         */
        bool update(double current_time_sec) override;

        /**
         * @brief Human readable status of object
         *
         * @return std::string
         */
        std::string pretty() override;

        /**
         * @brief Compute a new Machine Inertial Datum
         *
         * @param machine_inertial_data
         * @return true
         * @return false
         */
        bool new_machine_inertial_data(fast::rf::messages::SensorMsgs::ImuMsg machine_inertial_data) override;

       private:
        fast::rf::messages::GeometryMsgs::OdomMsg local_pose;
        bool excessive_rotate_accel{false};
        double normal_rotate_accel_timer{0.0};
        fast::rf::messages::GeometryMsgs::AccelMsg high_angular_accel;
    };
}  // namespace fast::rf::PoseSystem::LocalPoseSubsystem::LocalPoseFuser