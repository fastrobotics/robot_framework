# Generate Code Documentation
doxygen
if [ $? -ne 0 ]; then
    echo "❌ Error: Doxygen documentation Checking failed. Should FIX THIS!"
    #exit 1
fi

# Convert plantuml files to images
java -jar /usr/bin/plantuml.jar -r "**.puml"

# Convert dia files to images
#find . -type f -name "*.dia" -exec bash -c 'for f; do dia -t svg -n -e "${f%.dia}.svg" "$f"; done' _ {} +
git diff --name-only -- '*.dia' | xargs -I {} dia -t svg -n -e "{}"

# Check Markdown Links
markdown-link-check . -i build/ -q
if [ $? -ne 0 ]; then
    echo "❌ Error: Markdown Link Checking failed. Aborting commit."
    exit 1
fi