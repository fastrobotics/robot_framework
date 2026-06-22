java -jar /usr/bin/plantuml.jar -r "**.puml"
find . -type f -name "*.dia" -exec bash -c 'for f; do dia -t svg -n -e "${f%.dia}.svg" "$f"; done' _ {} +
