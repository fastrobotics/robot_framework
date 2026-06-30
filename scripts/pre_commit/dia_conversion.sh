#!/bin/bash
echo "Converting dia files to images..."
# All Files: find . -type f -name "*.dia" | xargs -I {} bash -c 'dia --export="${1%.dia}.png" "$1"' _ {}
git diff --staged --name-only --diff-filter=d -- '*.dia' |  xargs -I {} bash -c 'dia --export="${1%.dia}.png" "$1"' _ {}
echo "Ok!"