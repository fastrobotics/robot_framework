[Architecture Decision Records](../ADR.md)

- [ADR: Naming Conventions](#adr-naming-conventions)
- [Description](#description)
  - [Name components for what they DO, not what data they manipulate](#name-components-for-what-they-do-not-what-data-they-manipulate)
  - [Namespace hierarchy](#namespace-hierarchy)
  - [Namcespace vs Package usage](#namcespace-vs-package-usage)
  - [Function Naming](#function-naming)
- [Alternatives Investigated](#alternatives-investigated)
- [Implications](#implications)
  - [Middlware Context](#middlware-context)
- [Follow-up](#follow-up)
- [Deviations](#deviations)

# ADR: Naming Conventions

# Description

## Name components for what they DO, not what data they manipulate

The general idea behind this convention is to make it intuitively obvious what a specific component does. Here are some examples:
| What the component is | Good Name | Bad Name |
| --- | --- | --- |
| Computes Pose in a Global Frame | GlobalPose | NavOdometryComputer |
| Computes goals using a Behaviour Tree | GoalPlanner | BehaviorTreePlanner |

## Namespace hierarchy

Modules should be named according to the following convention. As an example:
`fast`::`rf`::<system>::<subsystem>::<process>

This practice prevents namespace collisions, and inforces proper dependency management.

## Namcespace vs Package usage

Packages are used in the following use cases:

- Catkin `packages`

Here packages should following the same definition as a namespace.

## Function Naming

While there can be a variety of valid function names, the following are some preferred recommendations:

| Function     | Purpose                                                                                                                                                                  |
| ------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `new_<blah>` | Pass data to a function. Implies some level of processing (though can be trivial or zero).                                                                               |
| `set_<blah>` | Assign data to a function. Implies practically NO processing, data is set blindly. Some minor data enforcing is allowed, such as array boundaries                        |
| `get_<blah>` | Retreive data. Can be processing implied, such as getting a value from an array and popping that element from the array. Strongly consider however the impact on a user. |

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
