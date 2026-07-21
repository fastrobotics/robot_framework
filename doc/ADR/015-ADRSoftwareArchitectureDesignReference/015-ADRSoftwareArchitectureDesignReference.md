[Architecture Decision Records](../ADR.md)

- [ADR: SoftwareArchitectureDesignReference](#adr-softwarearchitecturedesignreference)
- [Description](#description)
- [Alternatives Investigated](#alternatives-investigated)
- [Design](#design)
- [Follow-up](#follow-up)
- [Deviations](#deviations)

# ADR: SoftwareArchitectureDesignReference

# Description
Software Architecture's can follow different styles.  This ADR attempts to provide a common reference for not only how SW should be constructed, and also to show how a design can be interpreted.



| Rule                                 | Justification                                                                                                                         |
| ------------------------------------ | ------------------------------------------------------------------------------------------------------------------------------------- |
| Not required to show full API        | The motivation behind all SW Architecture is to communicate useful information.  It's NOT meant to document every API to some module. |
| Not specific to programming language | My work typically involves multiple languages.  Don't want to restrict architecture to specific languages.                            |

# Alternatives Investigated
This architecture has largely been designed over my years of experience.  No real alternatives to me exist, beyond iterating and reviewing on my learnings.

# Design
![](puml/SoftwareArchitectureReferenceClassDiagram.png)

# Follow-up

This ADR should be revisited in the future based on the following:
- New learnings
- More complex software

# Deviations

Not following this practice may be unavoidable in some exceptions. These are detailed below:
