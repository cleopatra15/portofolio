# SLCheck: Symbolic Link Checker

> A robust Bash utility designed for Linux system administration to traverse complex directory hierarchies, detect broken symbolic links, and prevent infinite loops[cite: 2].

## Overview

Administrating Linux systems often involves managing complex file hierarchies where symbolic links (symlinks) can easily break or create infinite loops[cite: 2]. SLCheck is a custom Shell script that performs a recursive Depth-First Search (DFS) through a specified directory to validate symlinks[cite: 2]. 

## Key Features

* **DFS Traversal:** Implements a recursive Depth-First Search algorithm to efficiently navigate nested directories[cite: 2].
* **Broken Link Detection:** Identifies symlinks pointing to non-existent or inaccessible targets[cite: 2].
* **Cycle Prevention:** Includes cycle detection to prevent the script from falling into infinite loops caused by recursive symlinks[cite: 1, 2].
* **Edge-Case Handling:** Safely handles filenames containing spaces through rigorous quoting and array iteration[cite: 2].
* **Optional Flags:** Supports a `--follow-symlinks` argument to customize traversal behavior[cite: 1].

## Technical Stack

* **Language:** Bash Scripting (Linux)[cite: 2]
* **Core Primitives:** `ls`, `test`, `readlink`, and standard POSIX shell conditions[cite: 2]
* **Testing Environments:** Ubuntu Linux, Bash 5.0+, and volatile memory filesystems (`tmpfs`)[cite: 2]

## Usage

Make the script executable and run it against your target directory:

```bash
# Make the script executable
chmod +x slcheck.sh

# Run against a specific directory
./slcheck.sh /path/to/target_directory

# Run with follow-symlinks flag enabled
./slcheck.sh /path/to/target_directory --follow-symlinks
