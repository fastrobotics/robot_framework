[LocalPose Subsystem](../../../doc/Subsystem-LocalPose.md)

- [Process: InertialSensorFuser](#process-inertialsensorfuser)
- [Overview](#overview)
  - [Purpose](#purpose)
  - [General Requirements](#general-requirements)
- [Process Architecture](#process-architecture)
- [Inputs](#inputs)
- [Outputs](#outputs)
- [How It Works](#how-it-works)
  - [Detailed Documentation](#detailed-documentation)
  - [Class Diagram](#class-diagram)
  - [InertialSensorFuser Process Implementation](#inertialsensorfuser-process-implementation)
- [Usage Instructions](#usage-instructions)
- [Validation](#validation)

# Process: InertialSensorFuser

# Overview

## Purpose

This process's objective is to combine multiple IMU Sensor's into one singular IMU reading for an entire machine.

## General Requirements

# Process Architecture

![](dia/InertialSensorFuserProcessArchitecture.png)

# Inputs

The following inputs are required in order for this system to properly function.

| Input                 | DataType       | Description                             | Requirement |
| --------------------- | -------------- | --------------------------------------- | ----------- |
| IMU Sensor (multiple) | SensorMsgs/Imu | Multiple IMU Sensors installed on Robot |             |

# Outputs

The following outputs are provided by this system.

| Output      | DataType       | Description         | Usage |
| ----------- | -------------- | ------------------- | ----- |
| Machine IMU | SensorMsgs/Imu | Aggregated IMU Data |       |

# How It Works

## Detailed Documentation

![](../../../../../../../Legend.png)

## Class Diagram

![](puml/InertialSensorFuserProcessClassDiagram.png)

## InertialSensorFuser Process Implementation

| Status | Implementation                                                                               | Details                             |
| ------ | -------------------------------------------------------------------------------------------- | ----------------------------------- |
| NEW    | DummyInertialSensorFuserProcess                                                              | Used for generating fake data       |
| NEW    | [BasicInertialSensorFuserProcess](ProcessImplementation/Process-BasicInertialSensorFuser.md) | Trivial implentation, very limited. |

# Usage Instructions

# Validation
