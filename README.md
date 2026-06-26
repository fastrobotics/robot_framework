# FAST Robotics - Robot Framework

- [FAST Robotics - Robot Framework](#fast-robotics---robot-framework)
- [Architecture Decision Records](#architecture-decision-records)
- [Architecture](#architecture)
- [Messages](#messages)
- [Setup](#setup)
- [Build](#build)
- [Run Unit Tests (after running Build)](#run-unit-tests-after-running-build)
- [Templates](#templates)

# Architecture Decision Records

[ADR's](doc/ADR/ADR.md)

# Architecture

[Architecture](doc/Architecture/Architecture.md)

# Messages

[Messages](msgs/doc/Messages.md)

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
sudo apt install python3-cookiecutter build-essential cmake libgeographiclib-dev
sudo npm install -g markdown-link-check

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

# Templates

This project makes extensive use of cookiecutter templates.
| Template | Folder | Use Case |
| --- | --- | --- |
| MessagePackageDefinition | `templates/MessagePackageDefinition/` | Used to create a middleware-agnostic Message Package Definition. |
| System | `templates/System/` | Used to create a new System. |

To use these templates, run:

```bash
cookiecutter <Template Folder containing cookiecutter.json> -o <Output Directory>
```
