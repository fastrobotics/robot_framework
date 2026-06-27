[Architecture Decision Records](../ADR.md)

- [ADR: Unit Tests can use Stored Data](#adr-unit-tests-can-use-stored-data)
- [Description](#description)
  - [Rationale](#rationale)
- [Alternatives Investigated](#alternatives-investigated)
- [Implications](#implications)
- [Follow-up](#follow-up)
- [Deviations](#deviations)

# ADR: Unit Tests can use Stored Data

# Description

Unit Tests should be able to use logged data.

## Rationale

1. Testing content is typically user via low level unit tests due to their fast operation, minimal setup requirements, and direct printing options.

# Alternatives Investigated

Using real data at higher level of testing is more common in practice, due to the more direct nature of playback capabilities. However in my experience this can be cumbersome to deal with.

# Implications

Supporting this decision will require the following:

1. Having a middle-ware agnostic way of storing/retreiving data
2. Storing large amounts of data in a repo is not generally a good practice.

# Follow-up

This ADR should be revisited in the future based on the following:

- During development of features that require real-world data.

# Deviations

Not following this practice may be unavoidable in some exceptions. These are detailed below:
