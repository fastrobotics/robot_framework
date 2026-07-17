#!/bin/bash
echo "Auto-Formatting Code..."
git diff --staged --name-only --diff-filter=ACMR -- '*.cpp' '*.hpp' | xargs clang-format -i -style=file
git diff --staged --name-only --diff-filter=ACMR -- '*/CMakeLists.txt' | xargs cmake-format -i
