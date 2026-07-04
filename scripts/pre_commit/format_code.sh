#!/bin/bash
echo "Auto-Formatting Code..."
git diff --staged --name-only -- '*.cpp' '*.hpp' | xargs clang-format -i -style=file
git diff --staged --name-only -- '*/CMakeLists.txt' | xargs cmake-format -i
