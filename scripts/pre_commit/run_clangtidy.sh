#!/bin/bash
echo "Running Clang-Tidy Code..."
# 1. Capture the stdout of the tool while still printing it to the terminal screen
# We capture it into a variable to evaluate if any errors occurred.
OUTPUT=$(git diff -U0 --staged -- '*.cpp' '*.hpp' ':(exclude)templates' ':(exclude)build' | clang-tidy-diff -p1 -path build/)

# 2. Print the actual results out to the console so you can see the mistakes
echo "$OUTPUT"

# 3. Force the script to fail if any warnings or errors are found in the output text
if echo "$OUTPUT" | grep -qE "(warning:|error:)"; then
    echo "❌ Style check failed! Please fix the errors listed above before committing."
    exit 1
else
    echo "✅ Style check passed!"
    exit 0
fi

