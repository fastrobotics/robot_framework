#!/bin/bash
echo "Converting mermaid files to images..."
git diff --staged --name-only --diff-filter=d -- '*.mmd' | xargs -I {} bash -c 'mmdc -i "$1" -o "${1%.mmd}.png" --scale 2' _ {}
echo "Ok!"