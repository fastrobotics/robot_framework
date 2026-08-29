#!/bin/bash
echo "Running Clang-Tidy Code..."
# 1. Get the list of modified files
files=$(git diff --staged --name-only -- '**/*.cpp' '**/*.hpp' ':(exclude)templates/*' ':(exclude)builds/*')

# Exit quietly if no files were changed
if [ -z "$files" ]; then
    echo "[INFO] No modified C++ files found to analyze."
    exit 0
fi

# 2. Run clang-tidy, catch the output, and keep stderr visible
echo "[INFO] Analyzing modified files..."
output=$(echo "$files" | xargs -r run-clang-tidy -p build 2>&1)

# 3. Check if the output contains actual clang-tidy warnings/errors
if echo "$output" | grep -E "warning:|error:" > /dev/null; then
    # Print the raw clang-tidy output so you can read the issues
    echo "$output"
    echo ""
    echo "[WARNING] Clang-Tidy found issues in your staged changes!"
else
    echo "[INFO] Clang-Tidy passed! No issues found."
fi

# Explicitly exit with 0 so the script never fails your pipeline/commit hook
exit 0

