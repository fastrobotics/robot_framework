[HatDriver Process](../Process-HatDriver.md)

- [Process Implementation: Servo Hat Driver](#process-implementation-servo-hat-driver)
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
  - [Test Executable](#test-executable)
  - [Artifacts Provides](#artifacts-provides)
  - [Integration Steps](#integration-steps)
- [Validation](#validation)
- [Helpful Commands](#helpful-commands)
  - [I2C Query](#i2c-query)

# Process Implementation: Servo Hat Driver

# Document History

| Version Number | Date         | Author     | Change           |
| :------------: | ------------ | ---------- | ---------------- |
|       0        | 11-July-2027 | David Gitz | Drafted Document |
# Overview

## ToDo

| Item |
| ---- |

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

## Detailed Documentation

![](../../../../../../../../Legend.png)

## Class Diagram

# Usage Instructions
## Test Executable
A Test Executable is provided.  This executable changes based on the following architectures:
| Architecture | Driver               | Comments                                          |
| ------------ | -------------------- | ------------------------------------------------- |
| `x86_64`     | `MockServoHatDriver` | A Mock Servo Hat Driver that produces dummy data. |
| `armv7l`     | `ServoHatDriver`     | A Real Servo Hat Driver                           |

To use this, after building/installing, run the following:
```bash
./install/bin/exec_servohat_driver
```
## Artifacts Provides
The following artifacts are provided:
| Artifact                 | Description                                      |
| ------------------------ | ------------------------------------------------ |
| `basic_HatDriverProcess` | General Library that provides this functionality |


## Integration Steps

# Validation

# Helpful Commands
## I2C Query
`i2cdetect -y 1`