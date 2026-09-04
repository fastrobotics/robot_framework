`@compare_tag Process-Document v0.1`
[Navigation Executor Subsystem](../../../doc/Subsystem-NavigationExecutor.md)

- [Process: Trajectory Selector](#process-trajectory-selector)
- [Overview](#overview)
  - [Purpose](#purpose)
  - [General Requirements](#general-requirements)
- [Inputs](#inputs)
- [Outputs](#outputs)
- [How It Works](#how-it-works)
  - [Detailed Documentation](#detailed-documentation)
  - [Class Diagram](#class-diagram)
  - [Global Pose Process Implementations](#global-pose-process-implementations)
- [Usage Instructions](#usage-instructions)
- [Validation](#validation)

# Process: Trajectory Selector

# Overview

## Purpose

This process's objective is to take a list of Twist Commands and select which specific one to operate on.

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
- System: TODO
- Subsystem: TODO
- Process: TODO

The following Diagnostics are reported by this Process:
| Diagnostic Type | Description |
| --------------- | ----------- |

# How It Works

## Detailed Documentation

![](../../../../../../../Legend.png)

## Class Diagram

![](puml/TrajectorySelectorProcessClassDiagram.png)

## Global Pose Process Implementations

| Status | Implementation                                                                              | Details                             |
| ------ | ------------------------------------------------------------------------------------------- | ----------------------------------- |
| NEW    | DummyTrajectorySelectorProcess                                                              | Used for generating fake data       |
| NEW    | [BasicTrajectorySelectorProcess](ProcessImplementations/Process-BasicTrajectorySelector.md) | Trivial implentation, very limited. |

# Usage Instructions

# Validation
