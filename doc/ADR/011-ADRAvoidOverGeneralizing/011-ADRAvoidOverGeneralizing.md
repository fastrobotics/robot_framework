[Architecture Decision Records](../ADR.md)

- [ADR: Avoid Over-Generalizing](#adr-avoid-over-generalizing)
- [Description](#description)
- [Alternatives Investigated](#alternatives-investigated)
- [Implications](#implications)
- [Follow-up](#follow-up)
- [Deviations](#deviations)

# ADR: Avoid Over-Generalizing

# Description

Over-generalizing causes over-complexity and can be hard to maintain. For example, a process that generalizes all hardware input/output as abstract interfaces can be challenging.

# Alternatives Investigated

None

# Implications

The main implications of not over-generalizing is to have more focused SW modules. For example, instead of a general SW module that is driven entirely by configuration that can handle arbitrary input/output, have more specific modules that handle specific input/output data.

# Follow-up

This ADR should be revisited in the future based on the following:

# Deviations

Not following this practice may be unavoidable in some exceptions. These are detailed below:
