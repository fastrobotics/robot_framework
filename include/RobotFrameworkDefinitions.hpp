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
    enum class Level {
        UNKNOWN = 0,
        NOERROR = 1,
        DEBUG = 2,
        INFO = 3,
        NOTICE = 4,
        WARN = 5,
        ERROR = 6,
        FATAL = 7,
        END_OF_LIST = 8
    };
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
            END_OF_LIST = 12,      //!< Last item of list.  Used for range checks.
        };
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
            END_OF_LIST = 12,          //!< Last item of list.  Used for range checks.
        };
        inline std::string pretty(DiagnosticMessage type) {
            switch (type) {
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
        namespace ObjectFusionSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 1;  //!< Unique ID for ObjectFusion Subsystem
        }
        namespace GlobalAwarenessSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 2;  //!< Unique ID for Global Awareness Subsystem
        }
        namespace LocalAwarenessSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 3;  //!< Unique ID for Local Awareness Subsystem
        }
        namespace ObjectPredictionSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 4;  //!< Unique ID for  Object Prediction Subsystem
        }
    }  // namespace AwarenessSystem
    namespace CommsSystem {
        constexpr uint8_t SYSTEM_ID = 2;  //!< Unique ID for the Comms System
    }
    namespace DataStorageSystem {
        constexpr uint8_t SYSTEM_ID = 3;  //!< Unique ID for the Data Storage System
    }
    namespace GoalPlanningSystem {
        constexpr uint8_t SYSTEM_ID = 4;  //!< Unique ID for the Goal Planning System
    }
    namespace ImplementControlSystem {
        constexpr uint8_t SYSTEM_ID = 5;  //!< Unique ID for the Implement Control System
    }
    namespace ModeControlSystem {
        constexpr uint8_t SYSTEM_ID = 6;  //!< Unique ID for the Mode Control System
    }
    namespace PoseSystem {
        constexpr uint8_t SYSTEM_ID = 7;  //!< Unique ID for Pose System
        namespace InertialSensorSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 1;  //!< Unique ID for Inertial Sensor Subsystem
        }
        namespace GlobalSensorSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 2;  //!< Unique ID for Global Sensor Subsystem
        }
        namespace GlobalPoseSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 3;  //!< Unique ID for Global Pose Subsystem
        }
        namespace LocalPoseSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 4;  //!< Unique ID for  Local Pose Subsystem
        }
    }  // namespace PoseSystem
    namespace NavigationSystem {
        constexpr uint8_t SYSTEM_ID = 8;  //!< Unique ID for the Navigation System
        namespace GlobalPlannerSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 1;                      //!< Unique ID for Global Planner Subsystem
            constexpr uint8_t PROCESS_GLOBALPLANNER_MANAGER_ID = 1;  //!< Unique ID for Global Planner Manager Process
            constexpr uint8_t PROCESS_GLOBALPATH_STORAGE_ID = 2;     //!< Unique ID for Global Path Storage Process
            constexpr uint8_t PROCESS_FREESPACE_PLANNER_ID = 3;      //!< Unique ID for Free Space Planner Process
            constexpr uint8_t PROCESS_GLOBALPATH_ROUTEPLANNER_ID =
                4;  //!< Unique ID for Global Path Route Planner Process
        }           // namespace GlobalPlannerSubsystem
        namespace LocalPlannerSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 2;  //!< Unique ID for Local Planner Subsystem
        }
        namespace NavigationExecutorSubsystem {
            constexpr uint8_t SUBSYSTEM_ID = 3;                    //!< Unique ID for  Navigation Executor Subsystem
            constexpr uint8_t PROCESS_DRIVE_EXECUTOR_ID = 1;       //!< Unique ID for the Drive Executor Process
            constexpr uint8_t PROCESS_TRAJECTORY_SELECTOR_ID = 2;  //!< Unique ID for the Trajectory Selector Process
            constexpr uint8_t PROCESS_TRAJECTORY_CONTROLLER_ID =
                3;  //!< Unique ID for the Trajectory Controller Process
        }           // namespace NavigationExecutorSubsystem
    }               // namespace NavigationSystem
    namespace PerceptionSystem {
        constexpr uint8_t SYSTEM_ID = 9;  //!< Unique ID for the Perception System
    }
    namespace SafetySystem {
        constexpr uint8_t SYSTEM_ID = 10;  //!< Unique ID for the Safety System
    }
    namespace TerrainSystem {
        constexpr uint8_t SYSTEM_ID = 11;  //!< Unique ID for the Terrain System
    }
    namespace UserInterfaceSystem {
        constexpr uint8_t SYSTEM_ID = 12;  //!< Unique ID for the User Interface System
    }
}  // namespace fast::rf