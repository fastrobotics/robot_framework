[ModeManager Subsystem](../../../doc/Subsystem-ModeManager.md)

- [Process: ArmedStateManager](#process-armedstatemanager)
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
  - [ArmedStateManager Process Implementation](#armedstatemanager-process-implementation)
- [Usage Instructions](#usage-instructions)
- [Validation](#validation)

# Process: ArmedStateManager

# Document History

| Version Number | Date | Author | Change |
| :------------: | ---- | ------ | ------ |

# Overview

## Purpose

This process's objective is to continually evaluate the status of the robot along with whatever arm change request is received, and compute an Arm Command.

## General Requirements

# Process Architecture

![](dia/ArmedStateManagerProcessArchitecture.png)

# Inputs

The following inputs are required in order for this system to properly function.

| Input                 | DataType              | Description                                                                                                                              | Requirement |
| --------------------- | --------------------- | ---------------------------------------------------------------------------------------------------------------------------------------- | ----------- |
| Arm Change Request    | `ArmStateChangeSrv`   | A Service (request/response) that is used to request a change in the armed state of the robot.                                           |             |
| Ready To Arm Messages | `ReadyToArmStatusMsg` | A message that is provided by other processes that indicates if they are ready to arm.  Note that typically there will be many of these. |             |

# Outputs

The following outputs are provided by this system.

| Output      | DataType        | Description              | Usage                                                                                         |
| ----------- | --------------- | ------------------------ | --------------------------------------------------------------------------------------------- |
| Arm Command | `ArmCommandMsg` | The commanded Arm state. | Typically used by things that manipulate the robot's phyiscal environment, such as actuators. |

# How It Works

## Detailed Documentation

![](puml/ArmedStateMachineDiagram.png)

![](../../../../../../../Legend.png)

## Class Diagram

![](puml/ArmedStateManagerProcessClassDiagram.png)

## ArmedStateManager Process Implementation

| Status | Implementation                                                                                   | Details                       |
| ------ | ------------------------------------------------------------------------------------------------ | ----------------------------- |
| NEW    | DummyArmedStateManagerProcess                                                                    | Used for generating fake data |
| NEW    | [BasicArmedStateManagerProcess](../doc/ProcessImplementations/Process-BasicArmedStateManager.md) |

# Usage Instructions

# Validation
