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
- [Processes](#processes)
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

# Processes

| Status | Process                                                                                      |
| ------ | -------------------------------------------------------------------------------------------- |
| DRAFT  | [Sensor Input Handler](../Processes/SensorInputHandler/doc/Process-SensorInputHandler.md)    |
| DRAFT  | [Sensor Health Monitor](../Processes/SensorHealthMonitor/doc/Process-SensorHealthMonitor.md) |
| DRAFT  | [Sensor Fuser](../Processes/SensorFuser/doc/Process-SensorFuser.md)                          |
| DRAFT  | [FOV Extractor](../Processes/FOVExtractor/doc/Process-FOVExtractor.md)                       |
| NEW    | [Feature Detector](../Processes/FeatureDetector/doc/Process-FeatureDetector.md)              |



# Usage Instructions

# Validation
