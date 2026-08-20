/**
 * @file BasicInertialSensorFuserProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <BaseInertialSensorFuserProcess.hpp>

namespace fast::rf::PoseSystem::LocalPoseSubsystem::InertialSensorFuser {
    /**
     * @brief Minimal Implementation for a InertialSensorFuser Process
     *
     */
    class BasicInertialSensorFuserProcess : public BaseInertialSensorFuserProcess {
       public:
        BasicInertialSensorFuserProcess() : BaseInertialSensorFuserProcess() {}

        /**
         * @brief Initialize the object
         *
         * @param imu_count
         * @return true
         * @return false
         */
        bool init(uint8_t imu_count) override;

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
         * @brief Process a new IMU datum
         *
         * @param imu_index
         * @param imu_data
         * @return true
         * @return false
         */
        bool new_imu_data(uint8_t imu_index, fast::rf::messages::SensorMsgs::ImuMsg imu_data) override;

       private:
    };
}  // namespace fast::rf::PoseSystem::LocalPoseSubsystem::InertialSensorFuser