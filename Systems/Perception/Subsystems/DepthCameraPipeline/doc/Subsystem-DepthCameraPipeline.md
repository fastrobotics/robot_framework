`@compare_tag Subsystem-Document v0.1`

[Perception System](../../../doc/System-Perception.md)

- [Subsystem: DepthCameraPipeline](#subsystem-depthcamerapipeline)
- [Overview](#overview)
  - [Purpose](#purpose)
  - [General Requirements](#general-requirements)
- [Subsystem Architecture](#subsystem-architecture)
  - [Class Diagram](#class-diagram)
- [Inputs](#inputs)
- [Outputs](#outputs)
- [How It Works](#how-it-works)
  - [Questions](#questions)
  - [Detailed Documentation](#detailed-documentation)
  - [Software Content](#software-content)
- [Processes in the Pipeline](#processes-in-the-pipeline)
- [Usage Instructions](#usage-instructions)
- [Validation](#validation)

# Subsystem: DepthCameraPipeline

# Overview

## Purpose

The DepthCameraPipeline Subsystem's role in the Robot Framework is to provide a common Depth Camera processing functionality that can be leveraged in other perception subsystems.

## General Requirements
| Requirement                                                                                                                                | Description                                     |
| ------------------------------------------------------------------------------------------------------------------------------------------ | ----------------------------------------------- |
| Follows Interface requirements of Perception System                                                                                        | Includes contracts, data integrity, rates, etc. |
| Minimal Latency/Memory Requirement- Intent for this subsystem is to operate in shared memory as processing/transporting data is expensive. |
| All Sensor Data is transformed to the same frame before it is passed intothis subsystem.                                                   |

# Subsystem Architecture

![](../../../../../Legend.png)

![](mermaid/DepthCameraPipelineSubsystemArchitecture.png)

## Class Diagram

![](puml/DepthCameraPipelineSubsystemClassDiagram.png)

# Inputs

The following inputs are required in order for this system to properly function.

| Input                        | DataType                | Description | Requirement |
| ---------------------------- | ----------------------- | ----------- | ----------- |
| Depth Camera Point Cloud 1-N | `SensorMsgs/PointCloud` |             |             |

# Outputs

The following outputs are provided by this system.

| Output                           | DataType                | Description | Usage |
| -------------------------------- | ----------------------- | ----------- | ----- |
| Fused Depth Camera Point Cloud   | `SensorMsgs/PointCloud` |             |       |
| FOV Depth Camera Point Cloud 1-N | `SensorMsgs/PointCloud` |             |       |
| Point Cloud Object Features      | TBD                     |             |       |


# How It Works
## Questions
- What is the linkage between the Field of View Extractor and the Feature Detector?
## Detailed Documentation

## Software Content
The `DepthCameraPipelineSubsystem` class can be used to directly run all the child processes.

# Processes in the Pipeline

| Status | Process                                                                                      |
| ------ | -------------------------------------------------------------------------------------------- |
| DRAFT  | [Sensor Input Handler](../Processes/SensorInputHandler/doc/Process-SensorInputHandler.md)    |
| DRAFT  | [Sensor Health Monitor](../Processes/SensorHealthMonitor/doc/Process-SensorHealthMonitor.md) |
| DRAFT  | [Sensor Fuser](../Processes/SensorFuser/doc/Process-SensorFuser.md)                          |
| DRAFT  | [FOV Extractor](../Processes/FOVExtractor/doc/Process-FOVExtractor.md)                       |
| NEW    | [Feature Detector](../Processes/FeatureDetector/doc/Process-FeatureDetector.md)              |



# Usage Instructions
```cmake
target_link_libraries(<your library/binary> depthCameraPipelineSubsystem)
```

```cpp
#include <DepthCameraPipelineSubsystem.hpp> // Include the subsystem
using namespace fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem;
DepthCameraPipelineSubsystem subsystem;  // Declare the subsystem
subsystem.init(); // Initialize it
subsystem.addSignalToMonitor("sensor name", "data type", <expected rate (Hz)>, <rate rolerance (Perc)>); // Add signals to monitor
fast::rf::messages::SensorMsgs::PointCloudMsg pointCloud;
subsystem.newPointCloud(pointCloud, "sensor name"); // Feed it a Point Cloud
subsystem.update(currentTime); // Periodically update it
fast::rf::Logger::logInfo(subsystem.pretty()); // Output to console/log output file the status of the system
auto readyToArm = subsystem.get_ready_to_arm(); // Get Ready to Arm Object
auto diagnostics = subsystem.getDiagnostics(); // Get all Diagnostics
```
# Validation
