[Architecture Decision Records](../../ADR.md)

- [ADR: Naming Conventions](#adr-naming-conventions)
- [Description](#description)
  - [Namespace hierarchy](#namespace-hierarchy)
  - [Namcespace vs Package usage](#namcespace-vs-package-usage)
- [Alternatives Investigated](#alternatives-investigated)
- [Implications](#implications)
  - [Middlware Context](#middlware-context)
- [Follow-up](#follow-up)
- [Deviations](#deviations)

# ADR: Naming Conventions

# Description

## Namespace hierarchy

Modules should be named according to the following convention. As an example:
`fast`::`rf`::<system>::<subsystem>::<process>

This practice prevents namespace collisions, and inforces proper dependency management.

## Namcespace vs Package usage

Packages are used in the following use cases:

- Catkin `packages`

Here packages should following the same definition as a namespace.

# Alternatives Investigated

# Implications

## Middlware Context

When middleware is added to support this, the following namespace is implied.
Original namespace (example):

`fast::rf::Pose::GlobalPose::GPSProcess`

ROS v1 namespace (example):

`fast::rf_ros::Pose::GlobalPose::GPSProcessNode`

ROS v2 namespace (example):

`fast::rf_ros2::Pose::GlobalPose::GPSProcessNode`

# Follow-up

This ADR should be revisited in the future based on the following:

# Deviations

Not following this practice may be unavoidable in some exceptions. These are detailed below:
