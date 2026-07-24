[InertialSensor Subsystem](../../../doc/Subsystem-InertialSensor.md)

- [Process: IMU](#process-imu)
- [Todo during AB#1732](#todo-during-ab1732)
- [Overview](#overview)
  - [Purpose](#purpose)
  - [General Requirements](#general-requirements)
- [Process Architecture](#process-architecture)
- [Inputs](#inputs)
- [Outputs](#outputs)
- [How It Works](#how-it-works)
  - [Detailed Documentation](#detailed-documentation)
  - [Class Diagram](#class-diagram)
  - [Diagnostics](#diagnostics)
  - [Other IMU Process Implementation](#other-imu-process-implementation)
- [Usage Instructions](#usage-instructions)
  - [Artifacts Provided](#artifacts-provided)
  - [Integration Steps](#integration-steps)
- [Validation](#validation)

# Process: IMU

# Todo during AB#1732
- Consider a buffer for IMU Data instead of singular data
- How to get "new" data?  a tuple return ("new", and imu data)?
- Create test executable for driver
# Overview

## Purpose

This process's objective is to ???.

## General Requirements

# Process Architecture

![](dia/IMUProcessArchitecture.png)

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

![](puml/IMUProcessClassDiagram.png)

## Diagnostics
The following Diagnostics are reported by this Process:
| Diagnostic Type | Description                |
| --------------- | -------------------------- |
| `SOFTWARE`      | Software Diagnostics       |
| `SENSORS`       | General Sensor Diagnostics |

## Other IMU Process Implementation

| Status | Implementation  | Details                       |
| ------ | --------------- | ----------------------------- |
| NEW    | DummyIMUProcess | Used for generating fake data |


# Usage Instructions

## Artifacts Provided
The following artifacts are provided:
| Artifact     | Description                                      |
| ------------ | ------------------------------------------------ |
| `imuProcess` | General Library that provides this functionality |


## Integration Steps

# Validation
