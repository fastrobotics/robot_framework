[README](../../../README.md)

[Architecture](../../doc/Architecture/Architecture.md)

- [System: Awareness](#system-awareness)
- [Document History](#document-history)
- [Overview](#overview)
  - [Purpose](#purpose)
  - [General Requirements](#general-requirements)
- [System Architecture](#system-architecture)
- [Inputs](#inputs)
- [Outputs](#outputs)
- [How It Works](#how-it-works)
  - [Detailed Documentation](#detailed-documentation)
  - [Software Content](#software-content)
- [Subsystems](#subsystems)
  - [Package Diagram](#package-diagram)
- [Usage Instructions](#usage-instructions)
- [Validation](#validation)

# System: Awareness

# Document History

| Version Number | Date         | Author     | Change           |
| :------------: | ------------ | ---------- | ---------------- |
|       0        | 22-June-2026 | David Gitz | Drafted Document |

# Overview

## Purpose

The Awareness System's role in the Robot Framework is to make the robot "Aware" of all objects in the environment.

## General Requirements

# System Architecture

# Inputs

The following inputs are required in order for this system to properly function.

| Input | Description | Requirement |
| ----- | ----------- | ----------- |

# Outputs

The following outputs are provided by this system.
| Output | Description | Usage |
| --- | --- | --- |

# How It Works

## Detailed Documentation

## Software Content

# Subsystems

The following Subsystems are provided in this System:
| State | Subsystem | Purpose |
| --- | --- | --- |
| NEW | [Object Fusion](Subsystems/ObjectFusionSubsystem/ObjectFusionSubsystem.md) | Receives various sensor inputs and fuses them together to form a picture of the objects in the environment. |
| NEW | [Global Awareness](Subsystems/GlobalAwarenessSubsystem/GlobalAwarenessSubsystem.md) | From the Objects created/tracked in the Fusion process, computes a list of Global Objects (i.e. all) objects in the environment. |
| NEW | [Local Awareness](Subsystems/LocalAwarenessSubsystem/LocalAwarenessSubsystem.md) | From the Objects created/tracked in the Fusion process, computes a list of Local Objects (i.e. limited to the surroundings of the robot). |
| NEW | [Object Prediction](Subsystems/ObjectFusionSubsystem/ObjectFusionSubsystem.md) | Predicts where objects will be in the future. |

## Package Diagram

![](puml/SystemAwarenessPackageDiagram.png)

# Usage Instructions

Typically the software provided directly in this System is not used, but instead is used at the Process level. However for validation purposes abstract classes are provided to test interface connectivity.

# Validation
