/**
 * @file MockIMUDriver.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-07-23
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <IMUDriver/BaseIMUDriver.hpp>
#include <ImuMsg.hpp>
namespace fast::rf::PoseSystem::InertialSensorSubsystem::IMU {
    /**
     * @brief A Mock IMU Driver
     *
     */
    class MockIMUDriver : public BaseIMUDriver {
       public:
        /**
         * @brief Initialize the Mock Driver
         *
         * @param imu_device_name
         * @return true
         * @return false
         */
        bool init(std::string imu_device_name);
        /**
         * @brief Get a human readable string of the object
         *
         * @return std::string
         */
        std::string pretty() override;

        /**
         * @brief Update the object
         *
         * @param current_time_sec
         * @return true
         * @return false
         */
        bool update(double current_time_sec) override;
    };
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem::IMU