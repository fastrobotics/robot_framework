[ADR](../../../016-ADRGPUSoftwareDesign.md)
- [MathTest Example](#mathtest-example)
  - [Purpose](#purpose)
  - [Architecture](#architecture)
    - [Class Diagram](#class-diagram)
  - [Usage](#usage)
  - [Results](#results)
    - [x86 Laptop with NO GPU](#x86-laptop-with-no-gpu)
    - [Nvidia Jetson Orin Nano](#nvidia-jetson-orin-nano)


# MathTest Example

## Purpose
This Example's objectives are the following:
- Provide easily readable code that can be ran on CPU and GPU to show proper SW Architecture
- Prove that GPU is running content correctly
- Give insight on how to construct source-code and build artifacts

## Architecture
![](../../../../../../Legend.png)

### Class Diagram
![](puml/MathTestClassDiagram.png)

## Usage
To run this, do the following
**CMake Environment**
```bash
./install/bin/test_cpugpu_math_benchmark 
```

**Colcon/ROS2 Environment**
```bash
./install/robot_framework_ros2/bin/test_cpugpu_math_benchmark
```

## Results
### x86 Laptop with NO GPU
```bash
Total benchmark test time: 5.64336 seconds
```

### Nvidia Jetson Orin Nano
```bash
=== Final Sweep Summary ===
Vector Size | CPU (ms) | GPU (ms) | Speedup
1000 | 0.376789 | 0.114991 | 3.27668x
100000 | 37.4865 | 0.945031 | 39.667x
200000 | 75.0806 | 1.10083 | 68.2037x
300000 | 112.432 | 0.852786 | 131.841x
400000 | 149.884 | 1.59465 | 93.9915x
500000 | 187.28 | 1.86695 | 100.313x
600000 | 224.668 | 2.0847 | 107.77x
700000 | 263.56 | 2.34514 | 112.386x
800000 | 299.526 | 2.65993 | 112.607x
900000 | 337.301 | 2.98134 | 113.137x
1000000 | 377.538 | 3.32309 | 113.61x

Total benchmark test time: 12.9971 seconds

```