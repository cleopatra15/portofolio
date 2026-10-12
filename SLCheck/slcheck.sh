#!/bin/bash

# Default values
FOLLOW_SYMLINKS=false
TARGET_DIR=""

# Parse arguments
for arg in "$@"; do
    if [ "$arg" = "--follow-symlinks" ]; then
        FOLLOW_SYMLINKS=true
    elif [ -z "$TARGET_DIR" ]; then
        TARGET_DIR="$arg"
    fi
done

# Validate input
if [ -z "$TARGET_DIR" ]; then
    echo "Utilizare: $0 [--follow-symlinks] <director>"
    exit 1
fi

if [ ! -d "$TARGET_DIR" ]; then
    echo "Eroare: $TARGET_DIR nu este un director valid"
    exit 1
fi

# Associative array to track visited directories and prevent infinite loops
declare -A VISITED_INODES

# Core DFS function
process_directory() {
    local current_dir="$1"

    # Check for read and execute permissions
    if [ ! -r "$current_dir" ] || [ ! -x "$current_dir" ]; then
        echo "Avertisment: Nu pot accesa directorul $current_dir"
        return
    fi

    # Generate a unique ID for the directory based on Device ID and Inode
    local dir_id=$(stat -c "%d:%i" "$current_dir")

    # Check if we have already visited this inode (cycle detection)
    if [ -n "${VISITED_INODES[$dir_id]}" ]; then
        echo "Ciclu detectat sau director deja vizitat: $current_dir"
        return
    fi

    # Mark as visited
    VISITED_INODES[$dir_id]=1

    # Iterate through all items in the directory
    for entry in "$current_dir"/*; do
        if [ -L "$entry" ]; then
            # Check if the target of the symlink exists
            if [ ! -e "$entry" ]; then
                echo "[BROKEN LINK] $entry"
                continue
            fi
            # If the symlink points to a directory and the flag is set, traverse it
            if [ -d "$entry" ] && [ "$FOLLOW_SYMLINKS" = true ]; then
                process_directory "$entry"
            fi
        elif [ -d "$entry" ]; then
            # Normal directory traversal
            process_directory "$entry"
        fi
    done
}

echo "Analizez directorul: $TARGET_DIR"
process_directory "$TARGET_DIR"
