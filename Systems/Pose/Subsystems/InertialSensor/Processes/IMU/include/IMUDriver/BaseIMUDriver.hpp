/**
 * @file BaseIMUDriver.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-23
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <IMUDriver/IIMUDriver.hpp>
#include <ImuMsg.hpp>
namespace fast::rf::PoseSystem::InertialSensorSubsystem {
    /**
     * @brief Base IMU Driver
     *
     */
    class BaseIMUDriver : public IIMUDriver {
       public:
        /**
         * @brief Get the imu data
         *
         * @return fast::rf::messages::SensorMsgs::ImuMsg
         */
        fast::rf::messages::SensorMsgs::ImuMsg get_imu_data() override;

        /**
         * @brief Get the magnetic data
         *
         * @return fast::rf::messages::SensorMsgs::MagneticFieldMsg
         */
        fast::rf::messages::SensorMsgs::MagneticFieldMsg get_magnetic_data();

       protected:
        /**
         * @brief Initialize the base object.  Called by the concrete object.
         *
         * @param device
         * @return true
         * @return false
         */
        virtual bool init(IIMUDriver::IMUDevice device);

        /**
         * @brief Get a human readable string of the object.  Called by the concrete object.
         *
         * @return std::string
         */
        virtual std::string pretty();

        /**
         * @brief Update the base object.  Called by the concrete object.
         *
         * @param current_time_sec
         * @return true
         * @return false
         */
        virtual bool update(double current_time_sec);

        fast::rf::messages::SensorMsgs::ImuMsg imu_data;                 //!< IMU Data
        fast::rf::messages::SensorMsgs::MagneticFieldMsg magnetic_data;  //!< Magnetic Data
        double start_time{-1.0};                                         //!< When the driver was started
        double current_time_sec{-1.0};                                   //!< Current Time
    };
}  // namespace fast::rf::PoseSystem::InertialSensorSubsystem