/**
 * @file ILocalPoseFuserProcess.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 * @compare_tag Process-Interface v0.1
 */
#pragma once
#include <AccelWithCovarianceMsg.hpp>
#include <DiagnosticMsg.hpp>
#include <IProcess.hpp>
#include <ImuMsg.hpp>
#include <OdomMsg.hpp>
#include <ReadyToArmStatusMsg.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>

namespace fast::rf::PoseSystem::LocalPoseSubsystem::LocalPoseFuser {
    /**
     * @brief Interface for the LocalPoseFuser Process
     *
     */
    class ILocalPoseFuserProcess : public IProcess {
       public:
        static constexpr double HIGH_ANGULARRATE_DISARM_LIMIT =
            300.0;  //!< Angular Acceleration Limit to automatically disarm the robot, in rad/s^2 Make this user config
                    //!< during AB#1844
        static constexpr double HIGH_ANGULARRATE_DISARM_TIMER =
            300.0;  // How long to wait for normal angular accel before allowing to arm again.  Make this user config
                    // during AB#1844.
        ILocalPoseFuserProcess() = default;
        virtual ~ILocalPoseFuserProcess() = default;

        /**
         * @brief Initialize the object
         *
         * @return true
         * @return false
         */
        virtual bool init() = 0;

        /**
         * @brief Process a new Machine Inertial Datum
         *
         * @param machine_inertial_data
         * @return true
         * @return false
         */
        virtual bool new_machine_inertial_data(fast::rf::messages::SensorMsgs::ImuMsg machine_inertial_data) = 0;

        /**
         * @brief Get the local pose object
         *
         * @param local_pose
         * @param angular_acc
         * @return true If the data is new
         * @return false
         */
        virtual bool get_local_pose(fast::rf::messages::GeometryMsgs::OdomMsg& local_pose,
                                    fast::rf::messages::GeometryMsgs::AccelWithCovarianceMsg& angular_acc) = 0;
    };
}  // namespace fast::rf::PoseSystem::LocalPoseSubsystem::LocalPoseFuser
