[README](../../../README.md)

[Architecture](../../../doc/Architecture/Architecture.md)

- [System: Navigation](#system-navigation)
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

# System: Navigation

# Document History

| Version Number | Date | Author | Change |
| :------------: | ---- | ------ | ------ |

# Overview

## Purpose

The Navigation System's role in the Robot Framework is to ???.

## General Requirements

# System Architecture

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

- Global Planning
- Local Planning

## Detailed Documentation

## Software Content

# Subsystems

The following Subsystems are provided in this System:

| State | Subsystem                                                                    | Purpose                                                                                                              |
| ----- | ---------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------- |
| NEW   | [Global Planner](../Subsystems/GlobalPlanner/doc/Subsystem-GlobalPlanner.md) | Acts as a "Server" that can plan a path in the global frame.                                                         |
| NEW   | Local Planner                                                                | Given a path, will generate Drive Commands continuously.                                                             |
| NEW   | Navigation Executor                                                          | Given Drive Commands, will generae Base Machine commands suitable for some Base Machine component to move the robot. |

## Package Diagram

![](puml/SystemNavigationPackageDiagram.png)

# Usage Instructions

# Validation
