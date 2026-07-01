#!/bin/bash
echo "Checking Markdown Links..."
lychee '**/*.md' --exclude-path "templates/*" --exclude-path "build/*"
if [ $? -ne 0 ]; then
    echo "❌ Error: Markdown Link Checking failed. Aborting commit."
    exit 1
fi
echo "Ok!"