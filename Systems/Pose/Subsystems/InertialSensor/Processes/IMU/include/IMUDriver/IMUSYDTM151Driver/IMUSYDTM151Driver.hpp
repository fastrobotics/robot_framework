/**
 * @file IMUSYDTM151Driver.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-23
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <IMUDriver/BaseIMUDriver.hpp>

#include "EasyObjectDictionary.h"
#include "EasyProfile.h"

namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    /**
     * @brief Driver for IMU Sensor SYD TM151

     * Refer to
     https://github.com/fastrobotics/component_database/blob/master/Components/Electrical/Sensors/Inertial/InertialSensors.md#sensor-robotshop-tm151
     *
     */
    class IMUSYDTM151Driver : public BaseIMUDriver {
       public:
        /**
         * @brief Initialize the device
         *
         * @param device
         * @return true
         * @return false
         */
        bool init(IMUDevice device) override;
        /**
         * @brief Human readable data for the driver
         *
         * @return std::string
         */
        std::string pretty() override;
    };
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem