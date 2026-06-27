[Pose System](../../../doc/System-Navigation.md)

- [Subsystem: Global Planner](#subsystem-global-planner)
- [Document History](#document-history)
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

# Subsystem: Global Planner

# Document History

| Version Number | Date         | Author     | Change           |
| :------------: | ------------ | ---------- | ---------------- |
|       0        | 27-June-2026 | David Gitz | Drafted Document |

# Overview

## Purpose

The GlobalPlanner Subsystem's role in the Robot Framework is to plan navigable paths in the Global Frame.

## General Requirements

| Requirement            | Description                                                                                                                                                                    |
| ---------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| Server-based operation | It is assumed in general that the Global Planner may take some time to plan a path. As such the Subsystem should be designed to operate with other instances running parallel. |

# Subsystem Architecture

![](../../../../../Legend.png)

![](dia/GlobalPlannerSubsystemArchitecture.png)

## Class Diagram

![](puml/GlobalPlannerSubsystemClassDiagram.png)

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

- Path Storage
- Route Planner

## Detailed Documentation

## Software Content

# Processes

| Status | Process |
| ------ | ------- |

## Package Diagram

# Usage Instructions

# Validation
