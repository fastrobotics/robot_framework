[TeleopControl Process](../Process-TeleopControl.md)

- [Process Implementation: TeleopControl](#process-implementation-teleopcontrol)
- [Document History](#document-history)
- [Overview](#overview)
  - [ToDo](#todo)
  - [Purpose](#purpose)
  - [General Requirements](#general-requirements)
  - [Limitations](#limitations)
- [Process Architecture](#process-architecture)
- [Inputs](#inputs)
  - [Modes](#modes)
  - [Keypad Inputs Supported](#keypad-inputs-supported)
  - [Interface Inputs Supported](#interface-inputs-supported)
- [Outputs](#outputs)
- [How It Works](#how-it-works)
  - [Detailed Documentation](#detailed-documentation)
  - [Class Diagram](#class-diagram)
  - [Diagnostics](#diagnostics)
- [Usage Instructions](#usage-instructions)
  - [Artifacts Provides](#artifacts-provides)
  - [Integration Steps](#integration-steps)
- [Validation](#validation)

# Process Implementation: TeleopControl

# Document History

| Version Number | Date        | Author     | Change           |
| :------------: | ----------- | ---------- | ---------------- |
|       0        | 7-July-2026 | David Gitz | Drafted Document |

# Overview

## ToDo

| Item                                                                                    |
| --------------------------------------------------------------------------------------- |
| Investigate Joystick Driver (or whatever compatible hardware device) will be used first |

## Purpose

This specific Process Implementation provides a simple Joystick enabled controller input that produces viable TwistMsg commands.

## General Requirements
- Interface with typical Joystick Driver outputs via a common interface
- 
## Limitations

The following are a listing of all limitations in this module:

# Process Architecture

# Inputs
## Modes
The Following Operation Modes are supported for this Module:
| Mode                      | Description                                                                        |
| ------------------------- | ---------------------------------------------------------------------------------- |
| `OperationMode::RUN`      | Normal operation, takes keyboard input and generates output.                       |
| `OperationMode::KEY_TEST` | Test mode.  Prints out information when a Key is provided.  Does not drive output. |

## Keypad Inputs Supported
| Input       | Usage                                                 |
| ----------- | ----------------------------------------------------- |
| UP_ARROW    | Increase Forward Velocity (Max 100.0%, Configurable)  |
| DOWN_ARROW  | Decrease Forward Velocity (Max -100.0%, Configurable) |
| LEFT_ARROW  | Increase Turn Rate (Max -100.0%, Configurable)        |
| RIGHT_ARROW | Decrease Turn Rate (Max 100.0%, Configurable)         |
| SPACE_BAR   | Set Forward Velocity and Turn Rate to 0% (STOP)       |

## Interface Inputs Supported

The following inputs are required in order for this system to properly function.

| Input | DataType | Description | Requirement |
| ----- | -------- | ----------- | ----------- |

# Outputs

The following outputs are provided by this system.

| Output | DataType | Description | Usage |
| ------ | -------- | ----------- | ----- |

# How It Works
When a Key Event is pressed, the process will compute an updated TwistCmd to fit a "Desired Command" that other processes can then use for consumption.

## Detailed Documentation

![](../../../../../../../../Legend.png)

## Class Diagram
![](puml/BasicTeleopControlProcessClassDiagram.png)

## Diagnostics
The following Diagnostics are reported by this Process:
| Diagnostic Type | Description |
| --------------- | ----------- |

# Usage Instructions

## Artifacts Provides
The following artifacts are provided:
| Artifact                     | Description                                      |
| ---------------------------- | ------------------------------------------------ |
| `basic_TeleopControlProcess` | General Library that provides this functionality |


## Integration Steps

# Validation
