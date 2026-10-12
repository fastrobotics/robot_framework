`@compare_tag ProcessImplementation-Document v0.1`
[SensorFuser Process](../Process-SensorFuser.md)

- [Process Implementation: SensorFuser](#process-implementation-sensorfuser)
- [Overview](#overview)
  - [Purpose](#purpose)
  - [General Requirements](#general-requirements)
  - [Limitations](#limitations)
- [Process Architecture](#process-architecture)
- [Inputs](#inputs)
- [Outputs](#outputs)
- [How It Works](#how-it-works)
  - [Detailed Documentation](#detailed-documentation)
  - [Diagnostics](#diagnostics)
- [Usage Instructions](#usage-instructions)
  - [Artifacts Provided](#artifacts-provided)
  - [Integration Steps](#integration-steps)
- [Validation](#validation)

# Process Implementation: SensorFuser

# Overview

## Purpose

This implementation combines incoming depth-camera point clouds, removes
overlap, and filters the result through an `INoiseReducer` implementation.
`BaseNoiseReducer` contains shared configuration, input handling, and
preprocessing; the CPU and GPU backends provide radius-neighbor classification.

## General Requirements

## Limitations

The following are a listing of all limitations in this module:

# Process Architecture

`BasicSensorFuserProcess` owns the reducer as a
`std::unique_ptr<INoiseReducer>`. CMake selects one backend for the build:
`noiseReducerGPU` on Jetson Orin Nano, or `noiseReducerCPU` otherwise. Both
backend libraries depend on `baseNoiseReducer`; neither depends on the other.
The GPU target is compiled with CUDA C++17 and the
`--expt-relaxed-constexpr` option. GPU initialization failure is reported and
does not trigger a CPU fallback.

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

## Diagnostics
The following Diagnostics are reported by this Process:
| Diagnostic Type            | Description                             |
| -------------------------- | --------------------------------------- |
| `DiagnosticType::SOFTWARE` | Triggers if Sensor Fusion has an issue. |

# Usage Instructions

## Artifacts Provided
The following artifacts are provided:
| Artifact                   | Description                                      |
| -------------------------- | ------------------------------------------------ |
| `basic_SensorFuserProcess` | General Library that provides this functionality |
| `baseNoiseReducer`         | Shared NoiseReducer implementation used by both backends |
| `noiseReducerCPU`          | CPU backend, built for supported platforms |
| `noiseReducerGPU`          | CUDA backend, built and selected for Jetson Orin Nano |


## Integration Steps

# Validation
