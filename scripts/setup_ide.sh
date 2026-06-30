echo "Setting up IDE"
sudo apt update
pip install --upgrade pip
pip install pre-commit cmakelang
pipx install cmake-format
pushd ~/Downloads
wget https://github.com/plantuml/plantuml/releases/download/v1.2026.6/plantuml-1.2026.6.jar
sudo mv plantuml-*.jar /usr/bin/plantuml.jar
popd
sudo apt install clang-format lychee
python3 -m pip install --user cookiecutter