#!/bin/bash
echo "Converting plantuml files to images..."
git diff --staged --name-only --diff-filter=d -- '*.puml'  -- ':!templates/*'  | xargs -I {} java -jar /usr/bin/plantuml.jar "{}"
if [ $? -ne 0 ]; then
    echo "❌ Error: Plantuml Generation failed. Aborting Commit."
    exit 1
fi
echo "Ok!"