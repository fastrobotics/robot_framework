[Architecture Decision Records](../ADR.md)

- [ADR: Message Definition](#adr-message-definition)
- [Description](#description)
- [Alternatives Investigated](#alternatives-investigated)
- [Implications](#implications)
- [Follow-up](#follow-up)
- [Deviations](#deviations)

# ADR: Message Definition

# Description

Messages for the Robot Framework Should be defined in the following manner:

1. In a folder under `msgs` with the name `<GeneralType>Msgs`
2. In this folder, under an `include` folder, each specific message should be defined by a unique header file (one per header)
   1. Note: This does not require that there is only 1 class defined in this header file, as there will be supporting functions/utilities provided as well potentially.

3. Messages should not be defined off ROS messages natively (although ROS messages can be used as references to ensure message translation compatability)
4. There should not be any source (cpp) files required for the message (i.e. header-only)
5. There should be unit tests for each message that:
   1. Define the message contract
   2. Provide general use case documentation

6. Messages can depend on other Messages. Avoid circular dependencies
7. There should be a class diagram for each Message, with all attributes defined
8. Utilities for Messages provided directly can include:
   1. Data Encoding to other formats (protobuf, serial, etc)
   2. Printing functions
   3. Data Storage functions (csv, json, etc)
   4. Data Parsing functions (csv, json, etc)

# Alternatives Investigated

The alternative approach to this is to use the ROS IDL directly, however that would violate [ADR-Middlware Agnostic](../004-ADR-MiddlewareAgnostic/004-ADR-MiddlewareAgnostic.md).

# Implications

The implications of this are the following:

- There will be duplicate message definitions between this and ROS. However as ROS1 and ROS2 differ already in IDL, and it's desired for this content to be agnostic of that, that's a necessary/on-purpose decision.
- At the middle-ware level, there will need to be translation units for all these messages. Trying to keep the ROS v1 IDL spec (at least for more common messages) is therefore desired.

# Follow-up

This ADR should be revisited in the future based on the following: None

# Deviations

1. Currently the `GeometryMsgs`, `SensorMsgs`,and `StandardMsgs` namespaces do not follow this convention (all messages are defined in 1 GeometryMsgs.hpp file). This will be resolved in AB#1682.
