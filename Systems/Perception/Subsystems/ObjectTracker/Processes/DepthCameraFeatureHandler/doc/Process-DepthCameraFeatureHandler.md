`@compare_tag Process-Document v0.1`
[ObjectTracker Subsystem](../../../doc/Subsystem-ObjectTracker.md)

- [Process: DepthCameraFeatureHandler](#process-depthcamerafeaturehandler)
- [Overview](#overview)
  - [Purpose](#purpose)
  - [General Requirements](#general-requirements)
- [Inputs](#inputs)
- [Outputs](#outputs)
- [Diagnostics](#diagnostics)
- [How It Works](#how-it-works)
  - [Detailed Documentation](#detailed-documentation)
  - [Class Diagram](#class-diagram)
  - [DepthCameraFeatureHandler Process Implementation](#depthcamerafeaturehandler-process-implementation)
- [Usage Instructions](#usage-instructions)
- [Validation](#validation)

# Process: DepthCameraFeatureHandler

# Overview

## Purpose

This process's objective is to ???.

## General Requirements

# Inputs

The following inputs are required in order for this system to properly function.

| Input | DataType | Description | Requirement |
| ----- | -------- | ----------- | ----------- |

# Outputs

The following outputs are provided by this system.

| Output | DataType | Description | Usage |
| ------ | -------- | ----------- | ----- |

# Diagnostics
Processes in this Subsystem are defined by:
- System: `PerceptionSystem::SYSTEM_ID`
- Subsystem: `PerceptionSystem::ObjectTrackerSubsystem::SUBSYSTEM_ID`
- Process: `PerceptionSystem::ObjectTrackerSubsystem::PROCESS_DEPTHCAMERAFEATUREHANDLER_ID`

The following Diagnostics are reported by this Process:
| Diagnostic Type | Description |
| --------------- | ----------- |

# How It Works

## Detailed Documentation

![](../../../../../../../Legend.png)

## Class Diagram

![](puml/DepthCameraFeatureHandlerProcessClassDiagram.png)

## DepthCameraFeatureHandler Process Implementation

| Status | Implementation                                                                                            | Details                             |
| ------ | --------------------------------------------------------------------------------------------------------- | ----------------------------------- |
| NEW    | DummyDepthCameraFeatureHandlerProcess                                                                     | Used for generating fake data       |
| NEW    | [BasicDepthCameraFeatureHandlerProcess](ProcessImplementations/Process-BasicDepthCameraFeatureHandler.md) | Trivial implentation, very limited. |

# Usage Instructions

# Validation
