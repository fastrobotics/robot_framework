#!/bin/bash
echo "Running Clang-Tidy Code..."
git diff -U0 --staged -- '*.cpp' '*.hpp' | grep -vE '^(b/)?(templates/|build/)' | clang-tidy-diff -p1 -- -std=c++17
