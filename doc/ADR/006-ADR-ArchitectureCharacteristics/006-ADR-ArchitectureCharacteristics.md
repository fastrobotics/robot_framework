[Architecture Decision Records](../ADR.md)

- [ADR: Architecture Characteristics (AC)](#adr-architecture-characteristics-ac)
- [Description](#description)
  - [High Priority Characteristics (\< 5)](#high-priority-characteristics--5)
  - [Medium Priority Characteristics (\< 5)](#medium-priority-characteristics--5)
  - [Low Priority Characteristics (\< 10)](#low-priority-characteristics--10)
  - [AC's to Ignore](#acs-to-ignore)
- [Implications](#implications)
- [Follow-up](#follow-up)
- [Deviations](#deviations)

# ADR: Architecture Characteristics (AC)

# Description

Architecture Characteristics are design goals that should be prioritized on the application requirements and the development team's background.

## High Priority Characteristics (< 5)

| Characteristic             | Why this Priority                                                                                                                                                          |
| -------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Maintainability**        | It is envisioned that this framework will be created to serve the author's long term plans for robot development, and as such a high degree of maintainability is desired. |
| **Robustness**             | This system should be capable of being fairly fault-tolerant, and when a fault condition occurs, should notify a user.                                                     |
| **Extensibility**          | This system is characterized by its extensibility, offering developer directed development at will.                                                                        |
| **Leverageability/Re-Use** | Re-use of SW components, at least in their appropriate dependency chain, should be a primary concern.                                                                      |

## Medium Priority Characteristics (< 5)

| Characteristic               | Why this Priority                                                                                                                                                                                                                                                                                                                                                         |
| ---------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Performance**              | It is assumed that generally there is more than enough compute resources for this content when deployed on machine.                                                                                                                                                                                                                                                       |
| **Reliability/Safety**       | Safety in robotics platforms is typically strongly desired, but as the sensors required for this are not likely available, nor is high performance computing available, this AC is only slightly desired and is more dependent on maintaining the robot itself, and not as concerned with human/environment life (due to the simplistic nature of these robot platforms). |
| **Archivability**            | Data/Log Storage should be considered.                                                                                                                                                                                                                                                                                                                                    |
| **Supportability**           | System should be fairly easy to troubleshoot.                                                                                                                                                                                                                                                                                                                             |
| **Useability/Achievability** | System should be fairly easy to use by a person.                                                                                                                                                                                                                                                                                                                          |

## Low Priority Characteristics (< 10)

| Characteristic      | Why this Priority                                                                                                                                                                    |
| ------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **Scalability**     | Some consideration is implies for this AC, but only in the case of Software Scalability. Generally deploying multiple robot applications at once is out of scope for this framework. |
| **Configurability** | It is desired to have minimal to no configuration required for a general robot application. While some configuration is required, this should be the exception.                      |
| **Availability**    | Generally the application should be able to run for a long duration of time, but it's expected that human intervention is somewhat feasible in error conditions.                     |

## AC's to Ignore

The following AC's are specifically ignored due to their inapplicability to this application.
| Characteristic | Why being Ignored |
| --- | --- |
| **Continuity** | Disaster recovery is applicable only via a) git (code storage), dev computer up-time, and compute up-time, all of which are already covered via other mechanisms. |
| **Recoverability** | In case of a disaster, there are likely more pressing needs than getting this system to work again. |
| **Installability** | It is assumed that the system will only be deployed to a handful of compute instances at one time, but that those compute instances already have their OS software installed. |
| **Localization** | Unnecessary |
| **Portability** | It is assumed that all compute platforms selected to support will be Ubuntu based, and as such will necessarily be compatible for running most SW components. |
| **Upgradeability** | Since Run-Tie/Uptime is somewhat a trivail concern, the system should NOT be required to be capable of deploying new content while current content is already running. |
| **Accessiblity** | Its a robotics application with minimal human involvement. |
| **Authentication** | Use built-in authentication (ssh) methods. |
| **Authorization** | Minimal users, not necessary. |
| **Legal** | IP protected by LICENSE files, this is not necessary. |
| **Privacy** | No personal information stored. |
| **Security** | Encryption not necessary at this time. |

# Implications

The above lists the implications of each AC prioritized.

# Follow-up

This ADR should be revisited in the future based on the following:

1. Encryption/Security Concerns.

# Deviations

Not following this practice may be unavoidable in some exceptions. These are detailed below:
