[Architecture Decision Records](../ADR.md)

- [ADR: GPU Software Design](#adr-gpu-software-design)
- [Description](#description)
- [Requirements](#requirements)
- [Examples](#examples)
- [Alternatives Investigated](#alternatives-investigated)
- [Implications](#implications)
- [Follow-up](#follow-up)
- [Deviations](#deviations)

# ADR: GPU Software Design

# Description
This ADR provides guidance on how to properly design software to support a Graphics Processing Unit (GPU)

# Requirements
| Requirement                                  | Description                                                                                                                                                                                             |
| -------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Replaceable with CPU content                 | All GPU software should be replaceable with CPU software.  This helps when comparing algorithms, proving out functionality, and allowing to target the process unit that is most effective at run-time. |
| Caller unit decides where to run at run-time | The caller unit should be capable of running the content on CPU or GPU at run-time.  Additionally it should be capable of deciding where it is the most efficient.                                      |



# Examples
| Example                                             | Description                                                                                                                                                         |
| --------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [MathTest](examples/MathTest/doc/MathTest.md)       | A program that can run via CPU and optionally by GPU to show some basic math programs                                                                               |
| [OpenCVTest](examples/OpenCVTest/doc/OpenCVTest.md) | A program that creates an image and then performs some image processing functions on it, using the GPU and if available the GPU and then saves the resultant image. |

# Alternatives Investigated

# Implications

# Follow-up

This ADR should be revisited in the future based on the following:
- When new interesting CUDA API's/examples are interesting

# Deviations

Not following this practice may be unavoidable in some exceptions. These are detailed below:
