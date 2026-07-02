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

namespace fast::rf {
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