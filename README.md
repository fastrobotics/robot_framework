# FAST Robotics - Robot Framework

- [FAST Robotics - Robot Framework](#fast-robotics---robot-framework)
- [Architecture Decision Records](#architecture-decision-records)
- [Architecture](#architecture)
- [Messages](#messages)
- [Setup](#setup)
- [Build](#build)
- [Run Unit Tests (after running Build)](#run-unit-tests-after-running-build)
- [Templates](#templates)

# [Architecture Decision Records](doc/ADR/ADR.md)

# [Architecture](doc/Architecture/Architecture.md)

# [Messages](msgs/doc/Messages.md)

# Setup

Pre-Requisites:

- Ubuntu system running 26.04 LTS

1. Clone this repo.
2. Run the following:

```bash
cd <repo>
sudo apt update
pip install --upgrade pip
pip install pre-commit
pipx install cmake-format
pushd ~/Downloads
wget https://github.com/plantuml/plantuml/releases/download/v1.2026.6/plantuml-1.2026.6.jar
sudo mv plantuml-*.jar /usr/bin/plantuml.jar
popd
sudo apt install python3-cookiecutter
```

# Build

Run the following:

```bash
cd <repo>
mkdir build && cd build
cmake ..;cmake --build .;cmake --install .
```

# Run Unit Tests (after running [Build](#build))

Run the following:

```bash
cd <repo>
ctest
```

# Templates

This project makes extensive use of cookiecutter templates.
| Template | Folder | Use Case |
| --- | --- | --- |
| MessageDefinition | `templates/MessageDefinition/` | Used to create a middleware-agnostic Message Definition. |
| System | `templates/System/` | Used to create a new System. |

To use these templates, run:

```bash
cookiecutter <Template Folder containing cookiecutter.json> -o <Output Directory>
```
