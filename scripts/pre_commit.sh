# Generate Code Documentation
doxygen

# Convert plantuml files to images
java -jar /usr/bin/plantuml.jar -r "**.puml"

# Convert dia files to images
find . -type f -name "*.dia" -exec bash -c 'for f; do dia -t svg -n -e "${f%.dia}.svg" "$f"; done' _ {} +

# Check Markdown Links
markdown-link-check . -i build/ -q
if [ $? -ne 0 ]; then
    echo "❌ Error: Tests failed. Aborting commit."
    exit 1
fi