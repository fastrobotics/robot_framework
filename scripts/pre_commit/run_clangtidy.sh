#!/bin/bash
echo "Running Clang-Tidy Code..."

show_help() {
        cat <<EOF
Usage: $0 [OPTION]

Run clang-tidy on C++ files.

With no option, analyze staged .cpp and .hpp files.

Options:
    --all       Analyze all tracked .cpp and .hpp files.
    -h, --help  Show this help text.

Files under templates/ and builds/ are excluded.

Examples:
    $0
    $0 --all
EOF
}

case "${1:-}" in
    "")
        # Analyze staged C++ files by default.
        files=$(git diff --staged --name-only -- '**/*.cpp' '**/*.hpp' ':(exclude)templates/*' ':(exclude)builds/*')
        file_scope="staged"
        ;;
    --all)
        # Analyze all tracked C++ files in the repository.
        files=$(git ls-files -- '*.cpp' '*.hpp' ':(exclude)templates/*' ':(exclude)builds/*')
        file_scope="all"
        ;;
    -h|--help)
        show_help
        exit 0
        ;;
    *)
        show_help
        exit 2
        ;;
esac

# Exit quietly if no files were changed
if [ -z "$files" ]; then
    echo "[INFO] No $file_scope C++ files found to analyze."
    exit 0
fi

# 2. Run clang-tidy, catch the output, and keep stderr visible
echo "[INFO] Analyzing $file_scope files..."
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

