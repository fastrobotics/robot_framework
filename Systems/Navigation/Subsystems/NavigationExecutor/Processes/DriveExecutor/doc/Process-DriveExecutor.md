[Navigation Executor Subsystem](../../../doc/Subsystem-NavigationExecutor.md)

- [Process: Drive Executor](#process-drive-executor)
- [Overview](#overview)
  - [Purpose](#purpose)
  - [General Requirements](#general-requirements)
- [Inputs](#inputs)
- [Outputs](#outputs)
- [Diagnostics](#diagnostics)
- [How It Works](#how-it-works)
  - [Detailed Documentation](#detailed-documentation)
  - [Class Diagram](#class-diagram)
  - [Drive Executor Process Implementations](#drive-executor-process-implementations)
- [Usage Instructions](#usage-instructions)
- [Validation](#validation)

# Process: Drive Executor

# Overview

## Purpose

This process's objective is to take a Twist Command and convert to the specific machine platform drive commands.

## General Requirements

# Inputs

The following inputs are required in order for this system to properly function.

| Input              | DataType | Description                                                               | Requirement |
| ------------------ | -------- | ------------------------------------------------------------------------- | ----------- |
| Trajectory Command | TwistMsg | Data should be scaled to include max/min values +/- 100.0 in all members. |

# Outputs

The following outputs are provided by this system.

| Output       | DataType                                | Description                                                                                                | Usage |
| ------------ | --------------------------------------- | ---------------------------------------------------------------------------------------------------------- | ----- |
| Drive Output | Generic based on `IDriveExecutorOutput` | A generic interface that describes the drive outputs.  This will be different based on the robot platform. |       |

# Diagnostics
Processes in this Subsystem are defined by:
- System: `NavigationSystem::SYSTEM_ID`
- Subsystem: `NavigationSystem::NavigationExecutorSubsystem::SUBSYSTEM_ID`
- Process: `NavigationSystem::NavigationExecutorSubsystem::PROCESS_DRIVE_EXECUTOR_ID`

The following Diagnostics are reported by this Process:
| Diagnostic Type  | Description                                                |
| ---------------- | ---------------------------------------------------------- |
| `SOFTWARE`       | General Diagnostics related to software processing issues. |
| `REMOTE_CONTROL` | Triggered until Remote Control commands are received.      |

  
# How It Works

## Detailed Documentation

![](../../../../../../../Legend.png)

## Class Diagram

![](puml/DriveExecutorProcessClassDiagram.png)

## Drive Executor Process Implementations

| Status | Implementation                                                                     | Details                                         |
| ------ | ---------------------------------------------------------------------------------- | ----------------------------------------------- |
| NEW    | DummyDriveExecutorProcess                                                          | Used for generating fake data                   |
| NEW    | [BasicDriveExecutorProcess](ProcessImplementations/Process-BasicDriveExecutor.md)  | Trivial implentation, very limited.             |
| DRAFT  | [Tank Drive Executor Process](ProcessImplementations/Process-TankDriveExecutor.md) | Drive Executor applicable to Tank Drive robots. |

# Usage Instructions
- See specific Process Implementations for Usage Instructions.

# Validation
- See specific Process Implementations for Validation information.