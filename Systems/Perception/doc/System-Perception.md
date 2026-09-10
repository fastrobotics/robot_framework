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
  - [Questions](#questions)
  - [Ideas](#ideas)
    - [Region of Interest Isolator](#region-of-interest-isolator)
    - [Object Classifier](#object-classifier)
    - [Filters](#filters)
    - [Feature Extraction](#feature-extraction)
  - [Module Description](#module-description)
    - [Perception Sensors](#perception-sensors)
    - [Sensor Pipelines](#sensor-pipelines)
      - [Ultrasonic Pipeline](#ultrasonic-pipeline)
    - [Perception Integrity Monitor](#perception-integrity-monitor)
    - [Object Tracker](#object-tracker)
    - [SLAM](#slam)
    - [Pose Estimator](#pose-estimator)
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

## Questions
- Feature Extraction?

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

## Module Description
>> Put this detail in other documentation
### Perception Sensors
- Includes either custom or vendor drivers.  Minimal control to how they work

### Sensor Pipelines
- Standardize on interfaces
- Diagnostics
- Aggregators/Combiners
- How do the different sensor modalities modify the pipelines?
- Is there more to pipelines that this?  Should there be specific things that happen because of the specific sensor modalities?  For example, should there be some form of "Feature Extraction" that happens in lidar pipelines, that in principle is the same in camera pipeline, but works fundamentally different?

#### Ultrasonic Pipeline
- Feeds object tracking in near environment.  Sensor modality dictates that what it detects is more like "something is near me"
- Should this interface with Map Building?
- Doesn't an Ultrasonic Sensor in principle look like a curved pointcloud circular wall of with a radious of the distance to the detected object and a size fo the sensor FOV

### Perception Integrity Monitor
- Sensor Diagnostics should probably be part of Sensor Pipeline
- Other diagnostics should probably be part of the thing that's generating it

### Object Tracker
- Initializes Tracks, Object List
- Classification (static vs dynamic)
- Labeling (same as classification?)

### SLAM

### Pose Estimator
- Is this part of SLAM?
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