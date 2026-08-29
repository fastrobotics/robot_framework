/**
 * @file RobotFrameworkDefinitions.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief Common Definitions for Robot Framework
 * @version 0.1
 * @date 2026-07-01
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <cstdint>
#include <string>

namespace fast::rf {
    /**
     * @brief Level Enum
     *
     */
    enum class Level {
        UNKNOWN = 0,     //!< Unknown Level
        NOERROR = 1,     //!< No Error
        DEBUG = 2,       //!< Debug.  Consider removing code that uses this, this is for development purposes.
        INFO = 3,        //!< Information
        NOTICE = 4,      //!< Notify user, but nothing to worry about
        WARN = 5,        //!< Warn user, program is able to still execute
        ERROR = 6,       //!< Something is wrong, program will terminate
        FATAL = 7,       //!< Something is seriously wrong, entire application should terminate
        END_OF_LIST = 8  //!< No use typically, Last item of list.  Used for range checks.
    };
    /**
     * @brief Covert level to string
     *
     * @param level
     * @return std::string
     */
    inline std::string pretty(Level level) {
        switch (level) {
            case Level::UNKNOWN:
                return "UNKNOWN";
            case Level::NOERROR:
                return "NO ERROR";
            case Level::DEBUG:
                return "DEBUG";
            case Level::INFO:
                return "INFO";
            case Level::NOTICE:
                return "NOTICE";
            case Level::WARN:
                return "WARN";
            case Level::ERROR:
                return "ERROR";
            case Level::FATAL:
                return "FATAL";
            default:
                return pretty(Level::UNKNOWN);
        }
    }

    /**
     * @brief ArmedState Definition
     *
     */
    enum class ArmedState {
        UNKNOWN = 0,             //!< Unknown Level
        DISARMED = 1,            //!< Disarmed On Purpose.  Can be Armed.
        DISARMED_CANNOTARM = 2,  //!< Robot is Disarmed, but it cannot arm.
        ARMING = 3,              //!< Robot is Arming
        ARMED = 4,               //!< Robot is Armed
        END_OF_LIST = 5          //!< No use typically, Last item of list.  Used for range checks.

    };
    /**
     * @brief Pretty string for Armed State
     *
     * @param state
     * @return std::string
     */
    inline std::string pretty(ArmedState state) {
        switch (state) {
            case ArmedState::UNKNOWN:
                return "UNKNOWN";
            case ArmedState::DISARMED:
                return "DISARMED";
            case ArmedState::DISARMED_CANNOTARM:
                return "DISARMED-CANNOTARM";
            case ArmedState::ARMING:
                return "ARMING";
            case ArmedState::ARMED:
                return "ARMED";
            default:
                return pretty(ArmedState::UNKNOWN);
        }
    }
    /**
     * @brief Diagnostic Definitions
     *
     */
    namespace DiagnosticDefinition {
        /**
         * @brief DiagnosticType
         * @details The type of Diagnostic
         *
         */
        enum class DiagnosticType {
            UNKNOWN = 0,           //!< Unitialized Value
            UNKNOWN_TYPE = 1,      //!< A Type that is not defined yet.
            SOFTWARE = 2,          //!< Diagnostic related to software, logic,etc.
            COMMUNICATIONS = 3,    //!< Diagnostic related to communication
            SENSORS = 4,           //!< Diagnostic related to sensors
            ACTUATORS = 5,         //!< Diagnostic related to actuators
            DATA_STORAGE = 6,      //!< Diagnostic related to data storage
            REMOTE_CONTROL = 7,    //!< Diagnostic related to remote control
            POSE = 8,              //!< Diagnostic related to pose
            PLANNING = 9,          //!< Diagnostic related to planning
            TIMING = 10,           //!< Diagnostic related to timing
            SYSTEM_RESOURCE = 11,  //!< Diagnostic related to system resource usage
            END_OF_LIST = 12,      //!< No use typically, Last item of list.  Used for range checks.
        };
        /**
         * @brief Convert DiagnosticType to human readable string
         *
         * @param type
         * @return std::string
         */
        inline std::string pretty(DiagnosticType type) {
            switch (type) {
                case DiagnosticType::UNKNOWN:
                    return "UNKNOWN";
                case DiagnosticType::UNKNOWN_TYPE:
                    return "UNKNOWN TYPE";
                case DiagnosticType::SOFTWARE:
                    return "SOFTWARE";
                case DiagnosticType::COMMUNICATIONS:
                    return "COMMUNICATIONS";
                case DiagnosticType::SENSORS:
                    return "SENSORS";
                case DiagnosticType::ACTUATORS:
                    return "ACTUATORS";
                case DiagnosticType::DATA_STORAGE:
                    return "DATA STORAGE";
                case DiagnosticType::REMOTE_CONTROL:
                    return "REMOTE CONTROL";
                case DiagnosticType::POSE:
                    return "POSE";
                case DiagnosticType::PLANNING:
                    return "PLANNING";
                case DiagnosticType::TIMING:
                    return "TIMING";
                case DiagnosticType::SYSTEM_RESOURCE:
                    return "SYSTEM RESOURCE";
                case DiagnosticType::END_OF_LIST:
                    return pretty(DiagnosticType::UNKNOWN);
                default:
                    return pretty(DiagnosticType::UNKNOWN);
            }
            return pretty(DiagnosticType::UNKNOWN);
        }
        /**
         * @brief Diagnostic Message enum Definition
         *
         */
        enum class DiagnosticMessage {
            UNKNOWN = 0,               //!< Unitialized value
            NOERROR = 1,               //!< No error
            NODATA = 2,                //!< No data
            UNKNOWN_ERROR = 3,         //!< Unknown error occured or Error not defined.
            INITIALIZING = 4,          //!< Initializing
            INITIALIZING_ERROR = 5,    //!< Error occured during initialization
            DROPPING_PACKETS = 6,      //!< Missing/Dropping messages
            MISSING_HEARTBEATS = 7,    //!< Missing heartbeat messages
            DEVICE_NOT_AVAILABLE = 8,  //!< Device is not currently available
            RESOURCE_LEAK = 9,         //!< Resource leakage occurring
            HIGH_RESOURCE_USAGE = 10,  //!< High resource usage
            DIAGNOSTIC_FAILED = 11,    //!< Diagnostic Failed
            END_OF_LIST = 12,          //!< No use typically, Last item of list.  Used for range checks.
        };
        /**
         * @brief Convert DiagnosticMessage to human readable string
         *
         * @param message
         * @return std::string
         */
        inline std::string pretty(DiagnosticMessage message) {
            switch (message) {
                case DiagnosticMessage::UNKNOWN:
                    return "UNKNOWN";
                case DiagnosticMessage::NOERROR:
                    return "NO ERROR";
                case DiagnosticMessage::NODATA:
                    return "NO DATA";
                case DiagnosticMessage::UNKNOWN_ERROR:
                    return "UNKNOWN ERROR";
                case DiagnosticMessage::INITIALIZING:
                    return "INITIALIZING";
                case DiagnosticMessage::INITIALIZING_ERROR:
                    return "INITIALIZING ERROR";
                case DiagnosticMessage::DROPPING_PACKETS:
                    return "DROPPING PACKETS";
                case DiagnosticMessage::MISSING_HEARTBEATS:
                    return "MISSING HEARTBEATS";
                case DiagnosticMessage::DEVICE_NOT_AVAILABLE:
                    return "DEVICE NOT AVAILABLE";
                case DiagnosticMessage::RESOURCE_LEAK:
                    return "RESOURCE LEAK";
                case DiagnosticMessage::HIGH_RESOURCE_USAGE:
                    return "HIGH RESOURCE USAGE";
                case DiagnosticMessage::DIAGNOSTIC_FAILED:
                    return "DIAGNOSTIC FAILED";
                case DiagnosticMessage::END_OF_LIST:
                    return pretty(DiagnosticMessage::UNKNOWN);
                default:
                    return pretty(DiagnosticMessage::UNKNOWN);
            }
        }
    }  // namespace DiagnosticDefinition

    namespace AwarenessSystem {
        constexpr uint8_t SYSTEM_ID = 1;  //!< Unique ID for the Awareness System
        struct Id {};
        inline const char* toString(Id) { return "awareness"; }
        namespace ObjectFusionSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 1;  //!< Unique ID for ObjectFusion Subsystem
            struct Id {};
            inline const char* toString(Id) { return "object_fusion"; }
        }  // namespace ObjectFusionSubsystem
        namespace GlobalAwarenessSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 2;  //!< Unique ID for Global Awareness Subsystem
            struct Id {};
            inline const char* toString(Id) { return "global_awareness"; }
        }  // namespace GlobalAwarenessSubsystem
        namespace LocalAwarenessSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 3;  //!< Unique ID for Local Awareness Subsystem
            struct Id {};
            inline const char* toString(Id) { return "local_awareness"; }
        }  // namespace LocalAwarenessSubsystem
        namespace ObjectPredictionSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 4;  //!< Unique ID for  Object Prediction Subsystem
            struct Id {};
            inline const char* toString(Id) { return "object_prediction"; }
        }  // namespace ObjectPredictionSubsystem
    }      // namespace AwarenessSystem
    namespace CommsSystem {
        constexpr uint8_t SYSTEM_ID = 2;  //!< Unique ID for the Comms System
        struct Id {};
        inline const char* toString(Id) { return "comms"; }
    }  // namespace CommsSystem
    namespace DataStorageSystem {
        constexpr uint8_t SYSTEM_ID = 3;  //!< Unique ID for the Data Storage System
        struct Id {};
        inline const char* toString(Id) { return "data_storage"; }
    }  // namespace DataStorageSystem
    namespace GoalPlanningSystem {
        constexpr uint8_t SYSTEM_ID = 4;  //!< Unique ID for the Goal Planning System
        struct Id {};
        inline const char* toString(Id) { return "goal_planning"; }
    }  // namespace GoalPlanningSystem
    namespace ImplementControlSystem {
        constexpr uint8_t SYSTEM_ID = 5;  //!< Unique ID for the Implement Control System
        struct Id {};
        inline const char* toString(Id) { return "implement_control"; }
    }  // namespace ImplementControlSystem
    namespace PoseSystem {
        constexpr uint8_t SYSTEM_ID = 6;  //!< Unique ID for Pose System
        struct Id {};
        inline const char* toString(Id) { return "pose"; }
        namespace InertialSensorSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 1;  //!< Unique ID for Inertial Sensor Subsystem
            struct Id {};
            inline const char* toString(Id) { return "inertial_sensor"; }
            namespace IMU {
                constexpr uint8_t PROCESS_IMU_ID = 1;  //!< Unique ID for IMU Process
                struct Id {};
                inline const char* toString(Id) { return "imu"; }
            }  // namespace IMU

        }  // namespace InertialSensorSubsystem
        namespace GlobalSensorSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 2;  //!< Unique ID for Global Sensor Subsystem
            struct Id {};
            inline const char* toString(Id) { return "global_sensor"; }
        }  // namespace GlobalSensorSubsystem
        namespace GlobalPoseSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 3;  //!< Unique ID for Global Pose Subsystem
            struct Id {};
            inline const char* toString(Id) { return "global_pose"; }
        }  // namespace GlobalPoseSubsystem
        namespace LocalPoseSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 4;  //!< Unique ID for  Local Pose Subsystem
            struct Id {};
            inline const char* toString(Id) { return "local_pose"; }
            namespace InertialSensorFuser {
                constexpr uint8_t PROCESS_INERTIALSENSORFUSER_ID = 1;  //!< Unique ID for Inertial Sensor Fuser
                struct Id {};
                inline const char* toString(Id) { return "inertial_sensor_fuser"; }
            }  // namespace InertialSensorFuser
            namespace WheelOdometryFuser {
                constexpr uint8_t PROCESS_WHEELODOMETRYFUSER_ID = 2;  //!< Unique ID for Wheel Odometry Fuser
                struct Id {};
                inline const char* toString(Id) { return "wheel_odometry_fuser"; }
            }  // namespace WheelOdometryFuser
            namespace VisualOdometryFuser {
                constexpr uint8_t PROCESS_VISUALODOMETRFUSER_ID = 3;  //!< Unique ID for Visual Odometry Fuser
                struct Id {};
                inline const char* toString(Id) { return "visual_odometry_fuser"; }
            }  // namespace VisualOdometryFuser
            namespace LocalPoseFuser {
                constexpr uint8_t PROCESS_LOCALPOSEFUSER_ID = 4;  //!< Unique ID for Local Pose Fuser
                struct Id {};
                inline const char* toString(Id) { return "local_pose_fuser"; }
            }  // namespace LocalPoseFuser

        }  // namespace LocalPoseSubsystem
    }      // namespace PoseSystem
    namespace NavigationSystem {
        constexpr uint8_t SYSTEM_ID = 7;  //!< Unique ID for the Navigation System
        struct Id {};
        inline const char* toString(Id) { return "navigation"; }
        namespace GlobalPlannerSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 1;  //!< Unique ID for Global Planner Subsystem
            struct Id {};
            inline const char* toString(Id) { return "goal_planner"; }
            namespace GlobalPlannerManager {
                constexpr uint8_t PROCESS_GLOBALPLANNER_MANAGER_ID =
                    1;  //!< Unique ID for Global Planner Manager Process
                struct Id {};
                inline const char* toString(Id) { return "global_planner_manager"; }
            }  // namespace GlobalPlannerManager
            namespace GlobalPathStorage {
                constexpr uint8_t PROCESS_GLOBALPATH_STORAGE_ID = 2;  //!< Unique ID for Global Path Storage Process
                struct Id {};
                inline const char* toString(Id) { return "global_path_storage"; }
            }  // namespace GlobalPathStorage
            namespace FreeSpacePlanner {
                constexpr uint8_t PROCESS_FREESPACE_PLANNER_ID = 3;  //!< Unique ID for Free Space Planner Process
                struct Id {};
                inline const char* toString(Id) { return "free_space_planner"; }
            }  // namespace FreeSpacePlanner
            namespace GlobalPathRoutePlanner {
                constexpr uint8_t PROCESS_GLOBALPATH_ROUTEPLANNER_ID =
                    4;  //!< Unique ID for Global Path Route Planner Process
                struct Id {};
                inline const char* toString(Id) { return "route_planner"; }
            }  // namespace GlobalPathRoutePlanner

        }  // namespace GlobalPlannerSubsystem
        namespace LocalPlannerSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 2;  //!< Unique ID for Local Planner Subsystem
            struct Id {};
            inline const char* toString(Id) { return "local_planner"; }
        }  // namespace LocalPlannerSubsystem
        namespace NavigationExecutorSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 3;  //!< Unique ID for  Navigation Executor Subsystem
            struct Id {};
            inline const char* toString(Id) { return "navigation_executor"; }
            namespace DriveExecutor {
                constexpr uint8_t PROCESS_DRIVE_EXECUTOR_ID = 1;  //!< Unique ID for the Drive Executor Process
                struct Id {};
                inline const char* toString(Id) { return "drive_executor"; }
            }  // namespace DriveExecutor
            namespace TrajectorySelector {
                constexpr uint8_t PROCESS_TRAJECTORY_SELECTOR_ID =
                    2;  //!< Unique ID for the Trajectory Selector Process
                struct Id {};
                inline const char* toString(Id) { return "trajectory_selector"; }
            }  // namespace TrajectorySelector
            namespace TrajectoryController {
                constexpr uint8_t PROCESS_TRAJECTORY_CONTROLLER_ID =
                    3;  //!< Unique ID for the Trajectory Controller Process
                struct Id {};
                inline const char* toString(Id) { return "trajectory_controller"; }
            }  // namespace TrajectoryController

        }  // namespace NavigationExecutorSubsystem
    }      // namespace NavigationSystem
    namespace PerceptionSystem {
        constexpr uint8_t SYSTEM_ID = 8;  //!< Unique ID for the Perception System
        struct Id {};
        inline const char* toString(Id) { return "perception"; }
    }  // namespace PerceptionSystem
    namespace SafetySystem {
        constexpr uint8_t SYSTEM_ID = 9;  //!< Unique ID for the Safety System
        struct Id {};
        inline const char* toString(Id) { return "safety"; }
        namespace ModeManagerSubsystem {
            const uint8_t SUBSYSTEM_ID = 1;  //!< Unique ID for the Mode Manager Subsystem
            struct Id {};
            inline const char* toString(Id) { return "mode_manager"; }

            namespace ArmedStateManager {
                constexpr uint8_t PROCESS_ARMEDSTATEMANAGER_ID = 1;  //!< Unique ID for the Armed State Manager Process
                struct Id {};
                inline const char* toString(Id) { return "armed_state_manager"; }
            }  // namespace ArmedStateManager
        }      // namespace ModeManagerSubsystem
    }          // namespace SafetySystem
    namespace TerrainSystem {
        constexpr uint8_t SYSTEM_ID = 10;  //!< Unique ID for the Terrain System
        struct Id {};
        inline const char* toString(Id) { return "terrain"; }
    }  // namespace TerrainSystem
    namespace UserInterfaceSystem {
        constexpr uint8_t SYSTEM_ID = 11;  //!< Unique ID for the User Interface System
        struct Id {};
        inline const char* toString(Id) { return "user_interface"; }
        namespace RemoteControlSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 1;  //!< Unique ID for the Remote Control Subsystem
            struct Id {};
            inline const char* toString(Id) { return "remote_control"; }
            namespace TeleopControl {
                constexpr uint8_t PROCESS_TELEOPCONTROL_ID = 1;  //!< Unique ID for Teleop Control Process
                struct Id {};
                inline const char* toString(Id) { return "teleop_control"; }
            }  // namespace TeleopControl

        }  // namespace RemoteControlSubsystem
    }      // namespace UserInterfaceSystem
    namespace BaseMachineSystem {
        const uint8_t SYSTEM_ID = 12;  //!< Unique ID for the Base Machine System
        struct Id {};
        inline const char* toString(Id) { return "base_machine"; }
        namespace BaseMachineSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 1;  //!< Unique ID for the Base Machine Subsystem
            struct Id {};
            inline const char* toString(Id) { return "base_machine"; }
            namespace HatDriver {
                constexpr uint8_t PROCESS_HATDRIVER_ID = 1;  //!< Unique ID for the Hat Driver Process
                struct Id {};
                inline const char* toString(Id) { return "hat_driver"; }
            }  // namespace HatDriver

        }  // namespace BaseMachineSubsystem
    }      // namespace BaseMachineSystem
}  // namespace fast::rf
