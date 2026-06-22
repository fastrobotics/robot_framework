[Architecture Decision Records](../../ADR.md)

- [ADR: Messaging System](#adr-messaging-system)
- [Description](#description)
  - [Messaging relation to Middle-Ware](#messaging-relation-to-middle-ware)
  - [Definition of an `action_state`](#definition-of-an-action_state)
- [Alternatives Investigated](#alternatives-investigated)
- [Implications](#implications)
- [Follow-up](#follow-up)
- [Deviations](#deviations)

# ADR: Messaging System

# Description

## Messaging relation to Middle-Ware

The Messaging System used (at a middle-ware level) should mimic the low-level API.

| Message Type | Example API                       |
| ------------ | --------------------------------- |
| Stream       | `void new_data(<blah>)`           |
| Service      | `bool new_data(<blah>)`           |
| Action       | `<action_state> new_data(<blah>)` |

## Definition of an `action_state`

The state of an action call is made up of at least the following:

- Some enum representing the status of the call
- An Action ID (Unique)
- Percent Complete

# Alternatives Investigated

# Implications

# Follow-up

This ADR should be revisited in the future based on the following:

# Deviations

Not following this practice may be unavoidable in some exceptions. These are detailed below:
