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
  - [Detailed Documentation](#detailed-documentation)
  - [Software Content](#software-content)
- [Processes](#processes)
  - [Package Diagram](#package-diagram)
- [Usage Instructions](#usage-instructions)
- [Validation](#validation)

# Subsystem: DepthCameraPipeline

# Overview

## Purpose

The DepthCameraPipeline Subsystem's role in the Robot Framework is to provide a common Depth Camera processing functionality that can be leveraged in other perception subsystems.

## General Requirements
| Requirement                                         | Description                                     |
| --------------------------------------------------- | ----------------------------------------------- |
| Follows Interface requirements of Perception System | Includes contracts, data integrity, rates, etc. |

# Subsystem Architecture

![](../../../../../Legend.png)

![](mermaid/DepthCameraPipelineSubsystemArchitecture.png)

## Class Diagram

![](puml/DepthCameraPipelineSubsystemClassDiagram.png)

# Inputs

The following inputs are required in order for this system to properly function.

| Input | DataType | Description | Requirement |
| ----- | -------- | ----------- | ----------- |

# Outputs

The following outputs are provided by this system.

| Output | DataType | Description | Usage |
| ------ | -------- | ----------- | ----- |

# How It Works
- Depth Camera Fuser
  - Overlap Detector (in overlap areas, should reduce error on detections, but remove redundant information)
- FOV Extractor
  - Able to  slice Combined data into smaller areas

- Standardize on interfaces
- Diagnostics
- Aggregators/Combiners
- How do the different sensor modalities modify the pipelines?
- Is there more to pipelines that this?  Should there be specific things that happen because of the specific sensor modalities?  For example, should there be some form of "Feature Extraction" that happens in lidar pipelines, that in principle is the same in camera pipeline, but works fundamentally different?
## Detailed Documentation

## Software Content

# Processes

| Status | Process |
| ------ | ------- |

## Package Diagram

# Usage Instructions

# Validation
