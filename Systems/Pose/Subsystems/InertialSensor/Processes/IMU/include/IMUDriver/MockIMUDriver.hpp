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
namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    /**
     * @brief A Mock IMU Driver
     *
     */
    class MockIMUDriver : public BaseIMUDriver {
       public:
        /**
         * @brief Initialize the Mock Driver
         *
         * @param device
         * @return true
         * @return false
         */
        bool init(IIMUDriver::IMUDevice device) override;
        /**
         * @brief Get a human readable string of the object
         *
         * @return std::string
         */
        std::string pretty() override;
    };
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem