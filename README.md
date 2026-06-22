# FAST Robotics - Robot Framework

- [FAST Robotics - Robot Framework](#fast-robotics---robot-framework)
- [Architecture Decision Records](#architecture-decision-records)
- [Setup](#setup)

# [Architecture Decision Records](doc/ADR.md)

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
```
