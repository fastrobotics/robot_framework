[{{cookiecutter.Subsystem}} Subsystem](../../../doc/Subsystem-{{cookiecutter.Subsystem}}.md)

- [Process: {{cookiecutter.Process}}](#process-cookiecutterprocess)
- [Overview](#overview)
  - [Purpose](#purpose)
  - [General Requirements](#general-requirements)
- [Inputs](#inputs)
- [Outputs](#outputs)
- [Diagnostics](#diagnostics)
- [How It Works](#how-it-works)
  - [Detailed Documentation](#detailed-documentation)
  - [Class Diagram](#class-diagram)
  - [{{cookiecutter.Process}} Process Implementation](#cookiecutterprocess-process-implementation)
- [Usage Instructions](#usage-instructions)
- [Validation](#validation)

# Process: {{cookiecutter.Process}}

# Overview

## Purpose

This process's objective is to ???.

## General Requirements

# Inputs

The following inputs are required in order for this system to properly function.

| Input | DataType | Description | Requirement |
| ----- | -------- | ----------- | ----------- |

# Outputs

The following outputs are provided by this system.

| Output | DataType | Description | Usage |
| ------ | -------- | ----------- | ----- |

# Diagnostics
Processes in this Subsystem are defined by:
- System: `{{cookiecutter.System}}System::SYSTEM_ID`
- Subsystem: `{{cookiecutter.System}}System::{{cookiecutter.Subystem}}Subsystem::SUBSYSTEM_ID`
- Process: `{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem::{{cookiecutter.Process_IDName}}`

The following Diagnostics are reported by this Process:
| Diagnostic Type | Description |
| --------------- | ----------- |

# How It Works

## Detailed Documentation

![](../../../../../../../Legend.png)

## Class Diagram

![](puml/{{cookiecutter.Process}}ProcessClassDiagram.png)

## {{cookiecutter.Process}} Process Implementation

| Status | Implementation                                                                                         | Details                             |
| ------ | ------------------------------------------------------------------------------------------------------ | ----------------------------------- |
| NEW    | Dummy{{cookiecutter.Process}}Process                                                                   | Used for generating fake data       |
| NEW    | [Basic{{cookiecutter.Process}}Process](ProcessImplementation/Process-Basic{{cookiecutter.Process}}.md) | Trivial implentation, very limited. |

# Usage Instructions

# Validation
