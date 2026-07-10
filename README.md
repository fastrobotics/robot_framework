# FAST Robotics - Robot Framework

- [FAST Robotics - Robot Framework](#fast-robotics---robot-framework)
- [ToDo List](#todo-list)
- [Architecture Decision Records](#architecture-decision-records)
- [ToDo](#todo)
  - [This PR](#this-pr)
- [Code Documentation](#code-documentation)
- [Architecture](#architecture)
- [Messages](#messages)
- [Setup](#setup)
- [Build](#build)
- [Run Unit Tests (after running Build)](#run-unit-tests-after-running-build)
- [Generate Code Coverage (after running Run Unit Tests)](#generate-code-coverage-after-running-run-unit-tests)
- [Templates](#templates)
# ToDo List
- Add remainder of System ID tests
- Flesh out Diagnostic attributes
- Add generic process interface with common functions that must be implemented
- Update templates
# Architecture Decision Records

[ADR's](doc/ADR/ADR.md)

# ToDo
## This PR
| Item |
| ---- |


# Code Documentation

[Code Documentation](https://fastrobotics.github.io/robot_framework/index.html)

# Architecture

[Architecture](doc/Architecture/Architecture.md)

# Messages

[Messages](msgs/doc/Messages.md)

# Setup

Pre-Requisites:

- Ubuntu system running 26.04 LTS

1. Clone this repo using:
```bash
git clone --recurse-submodules https://github.com/fastrobotics/robot_framework.git
git submodule update --remote
```
2. Run the following:

```bash
cd <repo>
./scripts/setup_ide.sh
./scripts/setup_robot.sh
```

# Build

Run the following:

```bash
cd <repo>
cmake -S . -B build
cmake --build build --target install -j20
```

# Run Unit Tests (after running [Build](#build))

Run the following:

```bash
cd <repo>
cd build
ctest
```

# Generate Code Coverage (after running [Run Unit Tests](#run-unit-tests-after-running-build))

```bash
./dev_tools/scripts/dev_tools.sh code_coverage
```

# Templates

This project makes extensive use of cookiecutter templates.

| Template                   | Folder                                  | Use Case                                                         |
| -------------------------- | --------------------------------------- | ---------------------------------------------------------------- |
| ArchitectureDecisionRecord | `templates/ArchitectureDecisionRecord/` | Used to create standard ADR.                                     |
| MessagePackageDefinition   | `templates/MessagePackageDefinition/`   | Used to create a middleware-agnostic Message Package Definition. |
| MessageDefinition          | `templates/MessageDefinition/`          | Used to create a new Message.                                    |
| System                     | `templates/System/`                     | Used to create a new System.                                     |
| Subsystem                  | `templates/Subsystem/`                  | Used to create a new Subsystem.                                  |
| Process                    | `templates/Process/`                    | Used to create a new Process                                     |

To use these templates, run:

```bash
cookiecutter <Template Folder containing cookiecutter.json> -o <Output Directory>
```
