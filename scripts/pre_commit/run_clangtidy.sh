#!/bin/bash
echo "Running Clang-Tidy Code..."
# ==============================================================================
# STEP 1: Strict Line-by-Line Style Check (Fails if violations > 0)
# ==============================================================================
echo "⏳ Checking staged lines for style violations..."

STAGED_OUTPUT=$(git diff -U0 --staged -- '*.cpp' '*.hpp' ':(exclude)templates' ':(exclude)build' | clang-tidy-diff -p1 -path build/)

# Count how many warnings are in the staged output
STAGED_COUNT=$(echo "$STAGED_OUTPUT" | grep -c "warning:")

echo "📊 Staged violations found: $STAGED_COUNT"

if [ "$STAGED_COUNT" -gt 0 ]; then
    echo "❌ Style check failed! Please fix the $STAGED_COUNT staging errors."
    exit 1
fi
exit 0


