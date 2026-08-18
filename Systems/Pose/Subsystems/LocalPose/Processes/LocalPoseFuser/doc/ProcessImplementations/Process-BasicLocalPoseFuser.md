[LocalPoseFuser Process](../Process-LocalPoseFuser.md)

- [Process Implementation: LocalPoseFuser](#process-implementation-localposefuser)
- [Overview](#overview)
  - [Purpose](#purpose)
  - [General Requirements](#general-requirements)
  - [Limitations](#limitations)
- [Process Architecture](#process-architecture)
- [Inputs](#inputs)
- [Outputs](#outputs)
- [How It Works](#how-it-works)
  - [Diagnostics](#diagnostics)
    - [Diagnostic Events](#diagnostic-events)
- [Usage Instructions](#usage-instructions)
  - [Artifacts Provided](#artifacts-provided)
  - [Integration Steps](#integration-steps)
- [Validation](#validation)

# Process Implementation: LocalPoseFuser

# Overview

## Purpose

This specific Process Implementation provides ???

## General Requirements

## Limitations

The following are a listing of all limitations in this module:

# Process Architecture

# Inputs

The following inputs are required in order for this system to properly function.

| Input | DataType | Description | Requirement |
| ----- | -------- | ----------- | ----------- |

# Outputs

The following outputs are provided by this system.

| Output | DataType | Description | Usage |
| ------ | -------- | ----------- | ----- |

# How It Works
This Basic Local Pose Fuser essentially is a pass-thru.

## Diagnostics
The following Diagnostics are reported by this Process:
| Diagnostic Type | Description                          |
| --------------- | ------------------------------------ |
| `SOFTWARE`      | General Software related Diagnostics |
| `POSE`          | Pose related Diagnostics             |

### Diagnostic Events
The following Events can trigger diagnostics in this module:
| Event                                                                                                           |
| --------------------------------------------------------------------------------------------------------------- |
| Not able to compute the differential between the current computed Odometry data and the previous Odometry data. |
| Excessive Angular Acceleration                                                                                  |


# Usage Instructions

## Artifacts Provided
The following artifacts are provided:
| Artifact                      | Description                                      |
| ----------------------------- | ------------------------------------------------ |
| `basic_LocalPoseFuserProcess` | General Library that provides this functionality |


## Integration Steps

# Validation
