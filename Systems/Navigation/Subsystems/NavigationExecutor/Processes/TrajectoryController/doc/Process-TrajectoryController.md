[Navigation Executor Subsystem](../../../doc/Subsystem-NavigationExecutor.md)

- [Process: Trajectory Controller](#process-trajectory-controller)
- [Overview](#overview)
  - [Purpose](#purpose)
  - [General Requirements](#general-requirements)
- [Inputs](#inputs)
- [Outputs](#outputs)
- [How It Works](#how-it-works)
  - [Detailed Documentation](#detailed-documentation)
  - [Class Diagram](#class-diagram)
  - [Trajectory Controller Process Implementations](#trajectory-controller-process-implementations)
- [Usage Instructions](#usage-instructions)
- [Validation](#validation)

# Process: Trajectory Controller

# Overview

## Purpose

This process's objective is to take a specifc Twist Command and the current robot Pose, and form a control loop to output a corrected Twist Command.

## General Requirements

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

![](puml/TrajectoryControllerProcessClassDiagram.png)

## Trajectory Controller Process Implementations

| Status | Implementation                                                                                  | Details                                                                     |
| ------ | ----------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------- |
| NEW    | DummyTrajectoryControllerProcess                                                                | Used for generating fake data                                               |
| NEW    | [BasicTrajectoryControllerProcess](ProcessImplementations/Process-BasicTrajectoryController.md) | PID Controller on Twist-Angular Z component.  Everything else is pass-thru. |

# Usage Instructions

# Validation
