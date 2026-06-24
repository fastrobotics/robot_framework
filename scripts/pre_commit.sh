# Generate Code Documentation
doxygen

# Convert plantuml files to images
java -jar /usr/bin/plantuml.jar -r "**.puml"

# Convert dia files to images
find . -type f -name "*.dia" -exec bash -c 'for f; do dia -t svg -n -e "${f%.dia}.svg" "$f"; done' _ {} +
