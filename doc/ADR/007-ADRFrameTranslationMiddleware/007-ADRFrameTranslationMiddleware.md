[Architecture Decision Records](../ADR.md)

- [ADR: Frame Translation is handled at Middleware Level](#adr-frame-translation-is-handled-at-middleware-level)
- [Description](#description)
  - [Rationale](#rationale)
- [Alternatives Investigated](#alternatives-investigated)
- [Implications](#implications)
- [Follow-up](#follow-up)
- [Deviations](#deviations)

# ADR: Frame Translation is handled at Middleware Level

# Description

Frame (transform Frames) should be translated, looked up, transformed, (any process) at the Middle-Ware Level.

## Rationale

1. ROS v1 provides this, with many utilities
2. ROS v2 provides this as well, at a presumably richer feature set
3. Middle-ware Agnostic Systems (and their children) don't tyically care about semantics about the frame, they will operate in a well defined frame, that the user (i.e. Middleware content) can freely decide. For example, a "Global Path Planning" module should be able to plan a path in any frame (including "local"), the Middleware content would be responsible for ensuring that this module was given data that was already transformed into the frame desired.

# Alternatives Investigated

Practically alternatives to this (transforms handled at any level) were not investigated due to the sheer nature of their complexity, the tools that already exist, and that it is irrelevant anyway.

# Implications

This decision has a few obvious implications:

1. A module may need to operate in multiple frames, but these should have well defined syntax, and no translation required. For example, the Navigation System will need to operate in at least a "Global" frame (for Global Planning) and a "Local" frame (for Local Planning), but these should be identified by name (i.e. `new_local_pose(...)`, `new_global_pose(...)` with the user (Middleware) responsible for calling the right function.
2. Because of the dynamic behaviour nature of frames, a given module may be operating on frame data that is older than desired (as it cannot do a direct translation). The ramifications of this are assumed to be minimal.
3. When a translation between frames is dynamic, the module using the frame should take this into consideration. For example, a Global Pose Process that is computing UTM coordinates based on Latitude/Longitude will have severe jumps at UTM zone changes.

# Follow-up

This ADR should be revisited in the future based on the following:

- When more complex usage and understanding of Frames is avaiable, including real-world data.

# Deviations

Not following this practice may be unavoidable in some exceptions. These are detailed below:
