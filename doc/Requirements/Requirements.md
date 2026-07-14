[README](../../README.md)

- [Requirements](#requirements)
- [Requirement Type: General](#requirement-type-general)
- [Requirement Type: Documentation](#requirement-type-documentation)
- [Requirement Type: Software Design](#requirement-type-software-design)
- [Requirement Type: Dependency Management](#requirement-type-dependency-management)

# Requirements

The following list all the requirements of this project.

# Requirement Type: General
The following are general requirements for this project.

| Requirement                   | Description                                                                                                                        |
| ----------------------------- | ---------------------------------------------------------------------------------------------------------------------------------- |
| Architecture Decision Records | ADR's shall be maintained, and adhered to.                                                                                         |
| SW Lifecycle Management       | SW that is not needed shall be deleted.  If required, this can be retreived via versioning tools.                                  |
| Project Management            | Azure Devops shall be used to manage the various work items for this content.  Access to Azure Devops for this project is assumed. |


# Requirement Type: Documentation
The following are requirements for this project related to Documentation.

| Requirement        | Description                                                                                                                |
| ------------------ | -------------------------------------------------------------------------------------------------------------------------- |
| Code Documentation | Doxygen shall be used for Code Documentation.  Documentation should be kept up to and checked via automated tools.         |
| SW Architecture    | All modules shall have at least a Class Diagram, and optionally a sequence diagram.                                        |
| Templates          | Templates shall be used extensively.  As the templates change over time, modules may need to be updated with new guidance. |

# Requirement Type: Software Design
The following are requirements for this project related to Software Design.

| Requirement             | Description                                                                                                                                                       |
| ----------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Follow SOLID principles | All Software created shall attempt to follow SOLID best practices                                                                                                 |
| Obvious design          | Software shall be designed to provide the minimum amount of surprise/maximum amount of implied assumptions.  i.e. a Module of name A should only do A, and not B. |
| File Location Proximity | Files should be located near each other.  For example, documentation relating to the design of SW should be located near the software implemented.                |



# Requirement Type: Dependency Management
The following are requirements for this project related to Dependencies.

| Requirement                                                                                       | Description                                                     |
| ------------------------------------------------------------------------------------------------- | --------------------------------------------------------------- |
| Follow [ADR-Middleware Agnostic](../ADR/004-ADR-MiddlewareAgnostic/004-ADR-MiddlewareAgnostic.md) | Naming this here to reflect the importance of this requirement. |
