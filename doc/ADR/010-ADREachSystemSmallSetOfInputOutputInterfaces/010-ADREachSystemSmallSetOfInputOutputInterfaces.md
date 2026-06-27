[Architecture Decision Records](../ADR.md)

- [ADR: Each System has small set of Input/Output Interfaces](#adr-each-system-has-small-set-of-inputoutput-interfaces)
- [Description](#description)
  - [Rationale](#rationale)
- [Alternatives Investigated](#alternatives-investigated)
- [Implications](#implications)
- [Follow-up](#follow-up)
- [Deviations](#deviations)

# ADR: Each System has small set of Input/Output Interfaces

# Description

Each System (and its children) should have a small set of Input/Output Interfaces

## Rationale

1. Modules that have a large interface boundary are hard to maintain, hard to test, brittle, and violate [ADR-Architecture Characteritics](../006-ADR-ArchitectureCharacteristics/006-ADR-ArchitectureCharacteristics.md#high-priority-characteristics--5).

# Alternatives Investigated

None

# Implications

The following implications are recognized from this Decision:

1. Over time, a given module's complexity can grow. However growth without some form of checks/balance should be avoided. There are no hard and fast rules here, the benefit of expanding the interface boundary of a module should be weighed with the cost of downstream maintenance.

# Follow-up

This ADR should be revisited in the future based on the following:

# Deviations

Not following this practice may be unavoidable in some exceptions. These are detailed below:
