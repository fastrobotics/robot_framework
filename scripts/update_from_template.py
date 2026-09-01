import argparse
import os
import re
import subprocess
import sys

# Matches: @compare_tag tag-name v1.2 (version is optional)
# Group 1: Tag Name, Group 2: Version String (if present)
TAG_REGEX = re.compile(r"[@\\]compare_tag\s+([a-zA-Z0-9_\-]+)(?:\s+(v?[0-9.]+))?")
MAX_SCAN_LINES = 50


def extract_tag_and_version(file_path):
    """Reads the top of a file to find a Doxygen comparison tag and version."""
    try:
        with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
            for _ in range(MAX_SCAN_LINES):
                line = f.readline()
                if not line:
                    break
                match = TAG_REGEX.search(line)
                if match:
                    tag = match.group(1)
                    # Keep as None if version isn't specified to identify completely missing tags
                    version = match.group(2) if match.group(2) else None
                    return tag, version
    except Exception as e:
        print(f"Error reading {file_path}: {e}")
    return None, None


def map_directory_tags(directory_path):
    """Scans a directory recursively and builds a map of {tag: [(file_path, version)]}."""
    tag_map = {}
    if not os.path.exists(directory_path):
        print(f"Error: Target directory does not exist: {directory_path}")
        return tag_map

    file_count = 0
    tag_count = 0
    
    for root, _, files in os.walk(directory_path, followlinks=True):
        for file in files:
            file_count += 1
            full_path = os.path.join(root, file)
            tag, version = extract_tag_and_version(full_path)
            if tag:
                tag_count += 1
                if tag not in tag_map:
                    tag_map[tag] = []
                tag_map[tag].append((full_path, version))

    print(f"  └─ Scanned {file_count} files. Found {tag_count} total tags ({len(tag_map)} unique).")
    return tag_map


def find_and_meld_by_tags(template_dir, impl_dir, force_all=False, dry_run=False):
    print(f"Scanning templates directory: {template_dir}")
    template_tags = map_directory_tags(template_dir)

    print(f"Scanning implementation directory: {impl_dir}")
    impl_tags = map_directory_tags(impl_dir)

    matched_tags = set(template_tags.keys()) & set(impl_tags.keys())

    if not matched_tags:
        print("\nNo matching tags found between templates and implementation files.")
        return

    print(f"\nEvaluating versions for matched tags...")

    comparisons_to_run = []

    for tag in sorted(matched_tags):
        for template_file, t_ver in template_tags[tag]:
            for impl_file, i_ver in impl_tags[tag]:
                
                # Check formatting variables for display logs
                t_display_ver = t_ver if t_ver else "[NO VERSION]"
                i_display_ver = i_ver if i_ver else "[NO VERSION]"

                # CORE UPDATE EVALUATION LOGIC:
                if force_all:
                    should_compare = True
                elif t_ver is None and i_ver is None:
                    # BOTH are missing versions -> they match, so skip!
                    should_compare = False
                elif t_ver is not None and i_ver is None:
                    # Template has a version but implementation is missing it -> needs update
                    should_compare = True
                else:
                    # Standard version string comparison
                    should_compare = (t_ver != i_ver)

                if should_compare:
                    comparisons_to_run.append((tag, template_file, t_display_ver, impl_file, i_display_ver))
                else:
                    print(f"  [SKIPPED] [{tag}] is matching/up-to-date ({i_display_ver}) for: {os.path.basename(impl_file)}")

    if not comparisons_to_run:
        print("\nAll files are completely up to date! Nothing to do.")
        return

    if dry_run:
        print(f"\n[DRY RUN] Found {len(comparisons_to_run)} files that need updating. Skipping Meld launch:")
        for tag, template_file, t_ver, impl_file, i_ver in comparisons_to_run:
            print(f"  * Would compare [{tag}] (Template: {t_ver} vs Impl: {i_ver})")
            print(f"    └─ Template path: {template_file}")
            print(f"    └─ Impl path:     {impl_file}")
        print("\nDry run completed safely.")
        return

    print(f"\nLaunching Meld for {len(comparisons_to_run)} target files...\n")

    for tag, template_file, t_ver, impl_file, i_ver in comparisons_to_run:
        print(f"Comparing Tag: [{tag}]")
        print(f"  ├─ Template v: {t_ver} -> {template_file}")
        
        # Color highlight missing version warnings if the template actually has one
        if i_ver == "[NO VERSION]":
            print(f"  └─ Impl v:     \033[91m{i_ver}\033[0m -> {impl_file}")
        else:
            print(f"  └─ Impl v:     {i_ver} -> {impl_file}")

        try:
            subprocess.run(["meld", template_file, impl_file], check=True)
        except FileNotFoundError:
            print("Error: 'meld' is not installed or not in your system PATH.", file=sys.stderr)
            sys.exit(1)
        except subprocess.CalledProcessError:
            print(f"Skipped or closed with error for tag: {tag}")
        print("-" * 40)


if __name__ == "__main__":
    SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
    REPO_ROOT = os.path.dirname(SCRIPT_DIR)
    
    DEFAULT_TEMPLATE_DIR = os.path.join(REPO_ROOT, "templates")
    DEFAULT_IMPL_DIR = os.path.join(REPO_ROOT, "implementation")

    parser = argparse.ArgumentParser(
        description="Recursively matches template and implementation files via Doxygen tags and runs Meld if versions mismatch."
    )
    parser.add_argument(
        "-t", "--templates",
        default=DEFAULT_TEMPLATE_DIR,
        help=f"Path to templates directory (default: {DEFAULT_TEMPLATE_DIR})"
    )
    parser.add_argument(
        "-i", "--impl",
        default=DEFAULT_IMPL_DIR,
        help=f"Path to implementation directory (default: {DEFAULT_IMPL_DIR})"
    )
    parser.add_argument(
        "-f", "--force",
        action="store_true",
        help="Force open Meld for all matching files, ignoring version matching rules."
    )
    parser.add_argument(
        "-d", "--dry-run",
        action="store_true",
        help="Run analysis and print planned operations without executing Meld."
    )

    args = parser.parse_args()

    abs_template_path = os.path.abspath(args.templates)
    abs_impl_path = os.path.abspath(args.impl)

    find_and_meld_by_tags(abs_template_path, abs_impl_path, force_all=args.force, dry_run=args.dry_run)
