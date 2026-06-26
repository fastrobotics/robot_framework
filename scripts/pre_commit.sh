echo "Generating Doxygen Documentation..."
doxygen
if [ $? -ne 0 ]; then
    echo "❌ Error: Doxygen documentation Checking failed. Aborting commit."
    exit 1
fi
echo "Ok!"

echo "Converting plantuml files to images..."
git diff --staged --name-only --diff-filter=d -- '*.puml'  -- ':!templates/*'  | xargs -I {} java -jar /usr/bin/plantuml.jar "{}"
if [ $? -ne 0 ]; then
    echo "❌ Error: Plantuml Generation failed. Aborting Commit."
    exit 1
fi
echo "Ok!"

echo "Converting dia files to images..."
git diff --staged --name-only --diff-filter=d -- '*.dia' | xargs -I {} dia -t svg -n -e "{}"
echo "Ok!"

echo "Checking Markdown Links..."
markdown-link-check . -i build/,templates/ -q
if [ $? -ne 0 ]; then
    echo "❌ Error: Markdown Link Checking failed. Aborting commit."
    exit 1
fi
echo "Ok!"