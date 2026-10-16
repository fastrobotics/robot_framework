`@compare_tag Process-Document v0.1`
[DepthCameraPipeline Subsystem](../../../doc/Subsystem-DepthCameraPipeline.md)

- [Process: FeatureDetector](#process-featuredetector)
- [Overview](#overview)
  - [Purpose](#purpose)
  - [General Requirements](#general-requirements)
- [Inputs](#inputs)
- [Outputs](#outputs)
- [Diagnostics](#diagnostics)
- [How It Works](#how-it-works)
  - [Detailed Documentation](#detailed-documentation)
  - [Class Diagram](#class-diagram)
  - [FeatureDetector Process Implementation](#featuredetector-process-implementation)
- [Usage Instructions](#usage-instructions)
- [Validation](#validation)

# Process: FeatureDetector

# Overview

## Purpose

This process's objective is to detect critical geometric features, specifically **Surface Normals** and **Fast Point Feature Histograms** to prepare the data for downstream object clustering and recognition.

## General Requirements

# Inputs

The following inputs are required in order for this system to properly function.

| Input                     | DataType                   | Description                                                                                  | Requirement |
| ------------------------- | -------------------------- | -------------------------------------------------------------------------------------------- | ----------- |
| Pre-Processed Point Cloud | `SensorMsgs/PointCloudMsg` | A Point Cloud that is downsampled and has noise reduced, to limit the processing complexity. |             |

# Outputs

The following outputs are provided by this system.

| Output               | DataType                   | Description                                                  | Usage |
| -------------------- | -------------------------- | ------------------------------------------------------------ | ----- |
| Features Point Cloud | `SensorMsgs/PointCloudMsg` | A Point Cloud that includes the original data plus features. |       |

# Diagnostics
Processes in this Subsystem are defined by:
- System: `PerceptionSystem::SYSTEM_ID`
- Subsystem: `PerceptionSystem::DepthCameraPipelineSubsystem::SUBSYSTEM_ID`
- Process: `PerceptionSystem::DepthCameraPipelineSubsystem::PROCESS_FEATUREDETECTOR_ID`

The following Diagnostics are reported by this Process:
| Diagnostic Type | Description |
| --------------- | ----------- |

# How It Works

## Detailed Documentation

![](../../../../../../../Legend.png)

## Class Diagram

![](puml/FeatureDetectorProcessClassDiagram.png)

## FeatureDetector Process Implementation

| Status | Implementation                                                                        | Details                             |
| ------ | ------------------------------------------------------------------------------------- | ----------------------------------- |
| NEW    | DummyFeatureDetectorProcess                                                           | Used for generating fake data       |
| NEW    | [BasicFeatureDetectorProcess](ProcessImplementations/Process-BasicFeatureDetector.md) | Trivial implentation, very limited. |

# Usage Instructions

# Validation
