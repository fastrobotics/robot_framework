[Architecture Decision Records](../ADR.md)

- [ADR: Naming Conventions](#adr-naming-conventions)
- [Description](#description)
- [Casing Conventions](#casing-conventions)
  - [Name components for what they DO, not what data they manipulate](#name-components-for-what-they-do-not-what-data-they-manipulate)
  - [Namespace hierarchy](#namespace-hierarchy)
  - [Namespace vs Package usage](#namespace-vs-package-usage)
  - [File Naming](#file-naming)
  - [Class/Struct Names](#classstruct-names)
  - [Function Naming](#function-naming)
  - [Variable Naming](#variable-naming)
    - [Prefix/Suffix Conventions](#prefixsuffix-conventions)
  - [Constants](#constants)
- [Further Reading](#further-reading)
- [Alternatives Investigated](#alternatives-investigated)
- [Implications](#implications)
  - [Middlware Context](#middlware-context)
- [Follow-up](#follow-up)
- [Deviations](#deviations)

# ADR: Naming Conventions

# Description

# Casing Conventions
The following case styles are typically used:
| Style        | Description                                    | Usage Requirements                                    |
| ------------ | ---------------------------------------------- | ----------------------------------------------------- |
| `snake_case` | All lowercase, words separated by underscores  | Used for external libraries, standard libraries, etc. |
| `camelCase`  | Starts lowercase, subsequent words capitalized | Typical content created in this and dependent content |
| `PascalCase` | Every word is capitalized                      | See Below.                                            |

## Name components for what they DO, not what data they manipulate

The general idea behind this convention is to make it intuitively obvious what a specific component does. Here are some examples:
| What the component is                 | Good Name   | Bad Name            |
| ------------------------------------- | ----------- | ------------------- |
| Computes Pose in a Global Frame       | GlobalPose  | NavOdometryComputer |
| Computes goals using a Behaviour Tree | GoalPlanner | BehaviorTreePlanner |

## Namespace hierarchy

Modules should be named according to the following convention. As an example:
`fast`::`rf`::<system>::<subsystem>::<process>

This practice prevents namespace collisions, and inforces proper dependency management.

## Namespace vs Package usage

Packages are used in the following use cases:

- Catkin `packages`

Here packages should following the same definition as a namespace.

## File Naming
Files should be named based on the following types:
| Type of File                                                                                 | Convention                                |
| -------------------------------------------------------------------------------------------- | ----------------------------------------- |
| A file about a class (Class Header, Implementation, Markdown document, SW Architecture, etc) | `PascalCase<ExtraInformation>.<Extenion>` |
| A file that implements a test for a Class                                                    | `test_PascalCase`                         |

## Class/Struct Names
Class Names and Structs should follow `PascalCase`.

## Function Naming

While there can be a variety of valid function names, the following are some preferred recommendations:

| Function        | Purpose                                                                                                                                                                  |
| --------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `new_camelCase` | Pass data to a function. Implies some level of processing (though can be trivial or zero).                                                                               |
| `set_camelCase` | Assign data to a function. Implies practically NO processing, data is set blindly. Some minor data enforcing is allowed, such as array boundaries                        |
| `get_camelCase` | Retreive data. Can be processing implied, such as getting a value from an array and popping that element from the array. Strongly consider however the impact on a user. |

## Variable Naming
Variable Naming conventions are important to make it easy to quickly understand the software.


### Prefix/Suffix Conventions
| Variable                    | Prefix/Suffix | Comments                                                                                                                      |
| --------------------------- | ------------- | ----------------------------------------------------------------------------------------------------------------------------- |
| Member variables in a class | `m_camelCase` | Objective is to quickly distinguish in reading order the encapsulation of an attribute (instead of having an `_`) at the end) |
| Global variables            | `g_camelCase` |                                                                                                                               |
| Static variables            | `s_camelCase` |
|                             |


## Constants
Constants should always be named in the form `UPPER_CASE_WITH_UNDERSCORES`.

# Further Reading
The more extensive style guide that is enforced can be found in the [clang-tidy file](../../../.clang-tidy].

# Alternatives Investigated
Style is highly subjective.  Important part is to be consistent, such that it becomes a non-issue.

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
1. In `puml` files, `package` will be used to indicate the focus of a current design.  For more information, see [ADR 015](../015-ADRSoftwareArchitectureDesignReference/015-ADRSoftwareArchitectureDesignReference.md).
