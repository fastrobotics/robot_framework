#!/bin/bash
echo "Running Clang-Tidy Code..."
git diff -U0 --staged -- '*.cpp' '*.hpp' ':(exclude)templates' ':(exclude)build' | clang-tidy-diff -p1 -path build/

