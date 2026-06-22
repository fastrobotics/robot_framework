[Architecture Decision Records](../../ADR.md)

- [ADR: Architecture Characteristics (AC)](#adr-architecture-characteristics-ac)
- [Description](#description)
  - [High Priority Characteristics](#high-priority-characteristics)
  - [Medium Priority Characteristics](#medium-priority-characteristics)
  - [Low Priority Characteristics](#low-priority-characteristics)
  - [Unprioritized (TODO)](#unprioritized-todo)
    - [Operational Architectural Characteristics](#operational-architectural-characteristics)
    - [Structural Architectural Characteristics](#structural-architectural-characteristics)
    - [Cross-Cutting Architectural Characteristics](#cross-cutting-architectural-characteristics)
- [Alternatives Investigated](#alternatives-investigated)
- [Implications](#implications)
- [Follow-up](#follow-up)
- [Deviations](#deviations)

# ADR: Architecture Characteristics (AC)

# Description

Architecture Characteristics are design goals that should be prioritized on the application requirements and the development team's background.

## High Priority Characteristics

| Characteristic      | Why this Priority                                                                                                                                                          |
| ------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Maintainability** | It is envisioned that this framework will be created to serve the author's long term plans for robot development, and as such a high degree of maintainability is desired. |

## Medium Priority Characteristics

| Characteristic         | Why this Priority                                                                                                                                                                                                                                                                                                                                                         |
| ---------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Performance**        | It is assumed that generally there is more than enough compute resources for this content when deployed on machine.                                                                                                                                                                                                                                                       |
| **Reliability/Safety** | Safety in robotics platforms is typically strongly desired, but as the sensors required for this are not likely available, nor is high performance computing available, this AC is only slightly desired and is more dependent on maintaining the robot itself, and not as concerned with human/environment life (due to the simplistic nature of these robot platforms). |

## Low Priority Characteristics

| Characteristic      | Why this Priority                                                                                                                                                                    |
| ------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **Scalability**     | Some consideration is implies for this AC, but only in the case of Software Scalability. Generally deploying multiple robot applications at once is out of scope for this framework. |
| **Configurability** | It is desired to have minimal to no configuration required for a general robot application. While some configuration is required, this should be the exception.                      |

## Unprioritized (TODO)

### Operational Architectural Characteristics

- **Availability**
- **Continuity**
- **Recoverability**
- **Robustness**

### Structural Architectural Characteristics

- **Extensibility**
- **Installability**
- **Leverageability/Re-Use**
- **Localization**
- **Portability**
- **Upgradeability**

### Cross-Cutting Architectural Characteristics

- **Accessiblity**
- **Archivability**
- **Authentication**
- **Authorization**
- **Legal**
- **Privacy**
- **Security**
- **Supportability**
- **Useability/Achievability**

# Alternatives Investigated

# Implications

# Follow-up

This ADR should be revisited in the future based on the following:

# Deviations

Not following this practice may be unavoidable in some exceptions. These are detailed below:
