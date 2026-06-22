[Architecture Decision Records](../ADR.md)

- [ADR: Middle-Ware Agnostic](#adr-middle-ware-agnostic)
- [Description](#description)
- [Alternatives Investigated](#alternatives-investigated)
- [Implications](#implications)
- [Follow-up](#follow-up)
- [Deviations](#deviations)

# ADR: Middle-Ware Agnostic

# Description

Content should be created to be agnostic of the specific Middleware's chosen (ROS v1, ROS v2, etc).

This is valid for the following reasons:

- ROS v1 is older, but still useful for a lot of development.
- ROS v2 is newer, more greenfield, and requires more investigation to understand how to implement correctly. It also provides multiple messaging mechanisms that core content shouldn't be dependent on.
- Being able to be agnostic from the middleware allows for much higher fidelity/timely unit test and development.

# Alternatives Investigated

# Implications

The following are implications of this Decision:

- A repo for middleware specific content will be required to extend this to allow execution in a real (or even simulated) environment. See [Naming Convention-Middlware Context](../002-ADR-NamingConventions/002-ADR-NamingConventions.md#middlware-context).
- There should not even be a message dependency (i.e. using ROS messages) in this content.
- Data Structures representing how components communicate should be created, and in the Middleware content will be required to have translation units for these.
- Other ROS dependencies (time, TF, Logger, etc) should be avoided.
- Middleware (ex: ROS Nodes) will need to be created to "wrap" content.

# Follow-up

This ADR should be revisited in the future based on the following:

# Deviations

Not following this practice may be unavoidable in some exceptions. These are detailed below:
