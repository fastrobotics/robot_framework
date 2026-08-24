#!/bin/bash
echo "Converting mermaid files to images..."
git diff --staged --name-only --diff-filter=d -- '*.mmd' | xargs -I {} bash -c 'mmdc -i "$1" -o "${1%.mmd}.png"' _ {}
echo "Ok!"