# Generate Code Documentation
doxygen
if [ $? -ne 0 ]; then
    echo "❌ Error: Doxygen documentation Checking failed. Should FIX THIS!"
    #exit 1
fi

# Convert plantuml files to images
git diff --name-only -- '*.puml'   | xargs -I {} java -jar /usr/bin/plantuml.jar "{}"
if [ $? -ne 0 ]; then
    echo "❌ Error: Plantuml Generation failed. Aborting Commit."
    exit 1
fi

# Convert dia files to images
git diff --name-only -- '*.dia' | xargs -I {} dia -t svg -n -e "{}"

# Check Markdown Links
markdown-link-check . -i build/ -q
if [ $? -ne 0 ]; then
    echo "❌ Error: Markdown Link Checking failed. Aborting commit."
    exit 1
fi