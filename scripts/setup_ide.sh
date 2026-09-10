echo "Setting up IDE"
sudo apt update
sudo apt install -y default-jre graphviz clang-tidy cmake-format clang-format mdutils
pushd ~/Downloads
wget https://github.com/plantuml/plantuml/releases/download/v1.2026.6/plantuml-1.2026.6.jar
sudo mv plantuml-*.jar /usr/bin/plantuml.jar
popd
snap install shfmt
pre-commit install
