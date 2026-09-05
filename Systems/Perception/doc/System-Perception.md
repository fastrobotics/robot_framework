`@compare_tag System-Document v0.1`
[README](../../../README.md)

[Architecture](../../../doc/Architecture/Architecture.md)

- [System: Perception](#system-perception)
- [Overview](#overview)
  - [Purpose](#purpose)
  - [General Requirements](#general-requirements)
- [System Architecture](#system-architecture)
- [Inputs](#inputs)
- [Outputs](#outputs)
- [How It Works](#how-it-works)
  - [Ideas](#ideas)
    - [Region of Interest Isolator](#region-of-interest-isolator)
    - [Object Classifier](#object-classifier)
    - [Filters](#filters)
    - [Feature Extraction](#feature-extraction)
  - [Detailed Documentation](#detailed-documentation)
  - [Software Content](#software-content)
- [Subsystems](#subsystems)
  - [Package Diagram](#package-diagram)
- [Usage Instructions](#usage-instructions)
- [Validation](#validation)
- [References](#references)
  - [Videos](#videos)

# System: Perception

# Overview

## Purpose

The Perception System's role in the Robot Framework is to ???.

## General Requirements

# System Architecture
![](mermaid/PerceptionSystemArchitecture.png)

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

- Camera
- Lidar
- Radar
- Perception Fusion

Goals of the Perception System are to:
1. Output a list of objects in the machine's surroundings
2. Output a map of the environment around the machine
3. Compute a pose based off the perceived environment

## Ideas
### Region of Interest Isolator
- Take in a set of data and subset it.  For example, a full 3D surround Lidar Point Cloud could be fed to this, that then just gives a narrow region in front of the robot, and/or a fixed distance from the robot.  Would be useful to do this with other data sources as well.
### Object Classifier
- Determines what classification of objects (moving, static), categories (people, vehicles, etc)
- AI?

### Filters
- Various filters used in Sensor Pipelines to clean up noisy data

### Feature Extraction
- Detect salient features from data sources
## Detailed Documentation

## Software Content

# Subsystems

The following Subsystems are provided in this System:
| State | Subsystem | Purpose |
| ----- | --------- | ------- |

## Package Diagram
![](../../../Legend.png)

![](puml/SystemPerceptionPackageDiagram.png)

# Usage Instructions

# Validation

# References
## Videos
- https://www.youtube.com/watch?v=L3cdMDIJqWs
- https://www.youtube.com/watch?v=_7zTL4If-Uw
- https://www.youtube.com/watch?v=UesfMYM4qcc
- https://www.youtube.com/watch?v=YoO5t7Lpl74