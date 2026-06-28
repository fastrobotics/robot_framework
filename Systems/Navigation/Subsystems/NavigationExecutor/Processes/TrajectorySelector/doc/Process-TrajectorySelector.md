[Navigation Executor Subsystem](../../../doc/Subsystem-NavigationExecutor.md)

- [Process: Trajectory Selector](#process-trajectory-selector)
- [Document History](#document-history)
- [Overview](#overview)
  - [Purpose](#purpose)
  - [General Requirements](#general-requirements)
- [Process Architecture](#process-architecture)
- [Inputs](#inputs)
- [Outputs](#outputs)
- [How It Works](#how-it-works)
  - [Detailed Documentation](#detailed-documentation)
  - [Class Diagram](#class-diagram)
  - [Global Pose Process Implementations](#global-pose-process-implementations)
- [Usage Instructions](#usage-instructions)
- [Validation](#validation)

# Process: Trajectory Selector

# Document History

| Version Number | Date | Author | Change |
| :------------: | ---- | ------ | ------ |

# Overview

## Purpose

This process's objective is to take a list of Twist Commands and select which specific one to operate on.

## General Requirements

# Process Architecture

![](dia/TrajectorySelectorProcessArchitecture.png)

# Inputs

The following inputs are required in order for this system to properly function.

| Input | DataType | Description | Requirement |
| ----- | -------- | ----------- | ----------- |

# Outputs

The following outputs are provided by this system.

| Output | DataType | Description | Usage |
| ------ | -------- | ----------- | ----- |

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
