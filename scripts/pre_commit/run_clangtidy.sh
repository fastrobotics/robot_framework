#!/bin/bash
echo "Running Clang-Tidy Code..."
git diff --staged --name-only --diff-filter=ACMR -- '*.cpp' '*.hpp' | grep -vE '^(templates/|build/)' | xargs -I {} clang-tidy {} -- -std=c++14
