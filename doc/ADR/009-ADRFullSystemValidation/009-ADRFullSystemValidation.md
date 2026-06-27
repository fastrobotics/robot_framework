[Architecture Decision Records](../ADR.md)

- [ADR: Full System Validation](#adr-full-system-validation)
- [Description](#description)
  - [Rationale](#rationale)
- [Alternatives Investigated](#alternatives-investigated)
- [Implications](#implications)
- [Follow-up](#follow-up)
- [Deviations](#deviations)

# ADR: Full System Validation

# Description

At every level of the Robot Framework, the application should be able to be validated at the unit test level.

## Rationale

1. Robots can be complicated, and hard to troubleshoot.
2. A Robot application is complex and not stable. Components are continually updated, refactored, abandoned, etc.

# Alternatives Investigated

None

# Implications

The following Implications are recognized from this Decision:

1. This requires a well thought out Architecture that is easily extendible (see [ADR - Architecture Characteristics: High Priority](../006-ADR-ArchitectureCharacteristics/006-ADR-ArchitectureCharacteristics.md#high-priority-characteristics--5).
2. This requires validation of content that would not typically be useful. For example, the PoseSystem would not typically be run directly on a robot, but instead each low level Process would have its own execution unit. However to ensure full interface validation, a mock of the full PoseSystem is required, that combines the full interface structure of all its children.
3. Full application level unit tests can be created (i.e. assign a mission, navigate to a goal, reach a goal, drop a payload, drive somewhere else).

# Follow-up

This ADR should be revisited in the future based on the following:

1. When some MVP is available for this framework, and this validation can be investigated more fully.

# Deviations

Not following this practice may be unavoidable in some exceptions. These are detailed below:
