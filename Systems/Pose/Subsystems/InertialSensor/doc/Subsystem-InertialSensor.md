[Pose System](../../../doc/System-Pose.md)

- [Subsystem: InertialSensor](#subsystem-cookiecuttersubsystem)
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

# Subsystem: InertialSensor

# Overview

## Purpose

The InertialSensor Subsystem's role in the Robot Framework is to ???

## General Requirements

# Subsystem Architecture

![](../../../../../Legend.png)

![](dia/InertialSensorSubsystemArchitecture.png)

## Class Diagram

![](puml/InertialSensorSubsystemClassDiagram.png)

# Inputs

The following inputs are required in order for this system to properly function.

| Input | DataType | Description | Requirement |
| ----- | -------- | ----------- | ----------- |

# Outputs

The following outputs are provided by this system.

| Output   | DataType             | Description              | Usage      |
| -------- | -------------------- | ------------------------ | ---------- |
| IMU Data | `SensorMsgs::ImuMsg` | IMU Data from IMU Sensor | Local Pose |

# How It Works

## Detailed Documentation

## Software Content

# Processes

| Status | Process                                           |
| ------ | ------------------------------------------------- |
| DRAFT  | [IMUProcess](../Processes/IMU/doc/Process-IMU.md) |

## Package Diagram

# Usage Instructions

# Validation
