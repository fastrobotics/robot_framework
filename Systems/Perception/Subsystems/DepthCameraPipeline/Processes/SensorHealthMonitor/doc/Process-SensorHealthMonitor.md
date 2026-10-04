`@compare_tag Process-Document v0.1`
[DepthCameraPipeline Subsystem](../../../doc/Subsystem-DepthCameraPipeline.md)

- [Process: SensorHealthMonitor](#process-sensorhealthmonitor)
- [Overview](#overview)
  - [Purpose](#purpose)
  - [General Requirements](#general-requirements)
- [Inputs](#inputs)
- [Outputs](#outputs)
- [Diagnostics](#diagnostics)
- [How It Works](#how-it-works)
  - [Detailed Documentation](#detailed-documentation)
  - [Class Diagram](#class-diagram)
- [Usage Instructions](#usage-instructions)
- [Validation](#validation)

# Process: SensorHealthMonitor

# Overview

## Purpose

This process's objective is to ???.

## General Requirements
| Requirement                    | Description                                                                                     |
| ------------------------------ | ----------------------------------------------------------------------------------------------- |
| 1 Active Sensor Health Monitor | The Sensor Health Monitor is responsible for monitoring all Depth Camera Pipeline Sensor Inputs |

# Inputs

The following inputs are required in order for this system to properly function.

| Input                      | DataType                | Description | Requirement |
| -------------------------- | ----------------------- | ----------- | ----------- |
| Depth Camera Point Cloud 1 | `SensorMsgs/PointCloud` |             |             |

NOTE: More Depth Camera's will be supported during AB#5755.
# Outputs

The following outputs are provided by this system.

| Output      | DataType | Description | Usage |
| ----------- | -------- | ----------- | ----- |
| Diagnostics |          |             |       |

# Diagnostics
Processes in this Subsystem are defined by:
- System: `PerceptionSystem::SYSTEM_ID`
- Subsystem: `PerceptionSystem::DepthCameraPipelineSubsystem::SUBSYSTEM_ID`
- Process: `PerceptionSystem::DepthCameraPipelineSubsystem::PROCESS_SENSORHEALTHMONITOR_ID`

The following Diagnostics are reported by this Process:
| Diagnostic Type            | Description                                                          |
| -------------------------- | -------------------------------------------------------------------- |
| `DiagnosticType::SOFTWARE` | General purpose Software Diagnostic                                  |
| `DiagnosticType::SENSORS`  | Checks for quality of sensor inputs.  Implemented during AB#5752.    |
| `DiagnosticType::TIMING`   | Checks for discrepencies in sensor timing (rates, out of order, etc) |

# How It Works
The Sensor Health Monitor sets up a list of signal health monitors that actively monitor the input signals and check for various health indicators (such as new data, missing data, etc).

Additionally the Sensor Health Monitor can look holistically at all the sensor data coming in, and trigger diagnostics that are more general/wholistic.

## Detailed Documentation

![](../../../../../../../Legend.png)

## Class Diagram

![](puml/SensorHealthMonitorProcessClassDiagram.png)

# Usage Instructions
```cmake
target_link_libraries(<binary or library> DepthCameraPipelineSubsystem::sensorHealthMonitorProcess)
```

```cpp
#include <SensorHealthMonitorProcess.hpp> // Include the Header
SensorHealthMonitorProcess process;  // Initialize the process
process.addSignalToMonitor("signal name", "signal datatype", <expected signal rate>, <rate tolerance>); // Add Signals to Monitor.
process.newPointCloud("signal name", <PointCloudMsg>); // Feed the Process data
process.update(<timestamp>); // Update the Process regularly.
```
# Validation
