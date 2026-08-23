[README](../../../README.md)

[Architecture](../../../doc/Architecture/Architecture.md)

- [System: Safety](#system-safety)
- [Overview](#overview)
  - [Purpose](#purpose)
  - [General Requirements](#general-requirements)
- [System Architecture](#system-architecture)
- [Inputs](#inputs)
- [Outputs](#outputs)
- [How It Works](#how-it-works)
  - [Detailed Documentation](#detailed-documentation)
    - [Armed State Machine](#armed-state-machine)
  - [Software Content](#software-content)
- [Subsystems](#subsystems)
  - [Package Diagram](#package-diagram)
- [Usage Instructions](#usage-instructions)
- [Validation](#validation)

# System: Safety

# Overview

## Purpose

The Safety System's role in the Robot Framework is to ensure the robot is always operating safely.

## General Requirements

# System Architecture
![](mermaid/SafetySystemArchitecture.mmd)

# Inputs

The following inputs are required in order for this system to properly function.

| Input | DataType | Description | Requirement |
| ----- | -------- | ----------- | ----------- |

# Outputs

The following outputs are provided by this system.

| Output | DataType | Description | Usage |
| ------ | -------- | ----------- | ----- |

# How It Works

Ideas:

- Diagnostics Aggregator
- Speed Limiter
- Joint Velocity Limiter
- System Resource Monitor (CPU, RAM, etc)

## Detailed Documentation
### Armed State Machine
![](../Subsystems/ModeManager/Processes/ArmedStateManager/doc/puml/ArmedStateMachineDiagram.png)

## Software Content

# Subsystems

The following Subsystems are provided in this System:
| State | Subsystem                                                              | Purpose                        |
| ----- | ---------------------------------------------------------------------- | ------------------------------ |
| DRAFT | [Mode Manager](../Subsystems/ModeManager/doc/Subsystem-ModeManager.md) | Manages Mode, Armed State, etc |
## Package Diagram
![](../../../Legend.png)

![](puml/SystemSafetyPackageDiagram.png)

# Usage Instructions

# Validation
