[Global Pose Process](../Process-GlobalPose.md)

- [Process Implementation: Basic Global Pose](#process-implementation-basic-global-pose)
- [Document History](#document-history)
- [Overview](#overview)
  - [ToDo](#todo)
  - [Purpose](#purpose)
  - [General Requirements](#general-requirements)
  - [Limitations](#limitations)
- [Process Architecture](#process-architecture)
- [Inputs](#inputs)
- [Outputs](#outputs)
- [How It Works](#how-it-works)
  - [Detailed Documentation](#detailed-documentation)
  - [Class Diagram](#class-diagram)
- [Usage Instructions](#usage-instructions)
- [Validation](#validation)

# Process Implementation: Basic Global Pose

# Document History

| Version Number | Date         | Author     | Change           |
| :------------: | ------------ | ---------- | ---------------- |
|       0        | 26-June-2026 | David Gitz | Drafted Document |

# Overview

## ToDo

| Item                                                                                        |
| ------------------------------------------------------------------------------------------- |
| Add specific Class Diagram                                                                  |
| Add Sequence Diagram                                                                        |
| Move Geo Conversion to separate library, other Concrete Processes will need to do the same. |

## Purpose

This specific Process Implementation provides an extremely simple way of computing a Global Pose given GPS Data.

## General Requirements

## Limitations

The following are a listing of all limitations in this module:

1. Minimal conversion supplied: Only converts Latitude and Longitude to UTM coordinates.
2. Due to UTM conversion process, will be severe jumps in converted position at zone boundaries, which are not currently detected.
3. No orientation computation provided.

# Process Architecture

# Inputs

The following inputs are required in order for this system to properly function.

| Input                                 | DataType                | Description                             | Requirement                 |
| ------------------------------------- | ----------------------- | --------------------------------------- | --------------------------- |
| GPS Sensor Data (**1 Instance Only**) | GlobalPositionSensorMsg | Position data in Geographic Coordinates | Interface spec is followed. |

# Outputs

The following outputs are provided by this system.

| Output         | DataType | Description                   | Usage                                                                                                                                       |
| -------------- | -------- | ----------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------- |
| GlobalOdometry | OdomMsg  | Singular Global Pose of robot | Best estimate of Global Pose. Note that this position may have discontinuties due to the nature of the GPS System, i.e. it is not "Smooth". |

# How It Works

## Detailed Documentation

![](../../../../../../../../Legend.png)

## Class Diagram

# Usage Instructions

# Validation
