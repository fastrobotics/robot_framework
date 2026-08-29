#!/bin/bash
echo "Running Clang-Tidy Code..."
#!/bin/bash

# ==============================================================================
# STEP 1: Strict Line-by-Line Style Check (Fails the script if errors are found)
# ==============================================================================
echo "⏳ Checking staged lines for style violations..."

STAGED_OUTPUT=$(git diff -U0 --staged -- '*.cpp' '*.hpp' ':(exclude)templates' ':(exclude)build' | clang-tidy-diff -p1 -path build/)

echo "$STAGED_OUTPUT"

if echo "$STAGED_OUTPUT" | grep -qE "(warning:|error:)"; then
    echo "❌ Style check failed! Please fix the staging errors above."
    exit 1
fi

# ==============================================================================
# STEP 2: Full Directory Scan (Informational only - will NEVER fail the script)
# ==============================================================================
echo ""
echo "🔍 Running informational scan across the entire project (excluding templates/ and build/)..."

# Regex breakdown:
# - Look inside any subdirectory: ^((?!templates|build).)*$
# - Target only C++ file extensions: \.(cpp|hpp|cc|cxx)$
FILE_REGEX="^((?!templates|build).)*\.(cpp|hpp|cc|cxx)$"

# run-clang-tidy uses multi-threading and automatically looks for compile_commands.json in build/
run-clang-tidy -p build/ -files "$FILE_REGEX"

# Force a success exit code regardless of what the full scan found
echo "✅ Full scan completed. Proceeding..."
exit 0


