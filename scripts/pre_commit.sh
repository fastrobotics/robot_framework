java -jar /usr/bin/plantuml.jar -r "**.puml"
find . -type f -name "*.dia" -exec bash -c 'for f; do dia --size=2000x -n -e "${f%.dia}.png" "$f"; done' _ {} +
