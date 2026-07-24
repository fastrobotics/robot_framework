/**
 * @file IIMUDriver.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-23
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <ImuMsg.hpp>
#include <string>
namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    /**
     * @brief Interface for an IMU Driver
     *
     */
    class IIMUDriver {
       public:
        /**
         * @brief Define all supported IMU's
         *
         */
        enum class IMUDevice {
            UNKNOWN = 0,   //!< Unknown IMU
            MOCK_IMU = 1,  //!< Mock, used for interface testing
            SYDTM151_IMU =
                2,  //!< Sensor:
                    //!< https://github.com/fastrobotics/component_database/blob/master/Components/Electrical/Sensors/Inertial/InertialSensors.md#sensor-robotshop-tm151
            END_OF_LIST = 3  //!< Last item of list. Used for Range Checks.
        };
        IIMUDriver() = default;
        virtual ~IIMUDriver() = default;
        virtual bool init(IMUDevice device) = 0;
        virtual std::string pretty() = 0;
        virtual fast::rf::messages::SensorMsgs::ImuMsg get_imu_data() = 0;
    };
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem