#!/bin/bash
#
# writer.sh
# Author: plushpluto
# Description:
#   This script creates a new file with specified content at a given path.
#   It will overwrite any existing file and create the directory path if 
#   it doesn't exist.
#
# Usage:
#   ./writer.sh <writefile> <writestr>
#
# Parameters:
#   writefile - full path to a file (including filename) on the filesystem
#   writestr  - text string which will be written within the file
#
# Requirements:
#   - mkdir command
#   - echo command
#   - dirname command
#
# Exit Codes:
#   0 - Success
#   1 - Invalid arguments or file creation failed
#

# Declaring the variables
writefile="$1"
writestr="$2"

# Check if both arguments are provided
if [ $# -ne 2 ]; then
    echo "Error: Two arguments required - writefile and writestr"
    echo "Usage: $0 <writefile> <writestr>"
    exit 1
fi

# Check if writefile argument is empty
if [ -z "$writefile" ]; then
    echo "Error: writefile argument cannot be empty"
    exit 1
fi

# Check if writestr argument is empty
if [ -z "$writestr" ]; then
    echo "Error: writestr argument cannot be empty"
    exit 1
fi

# Create the directory path if it doesn't exist
writedir=$(dirname "$writefile")
if ! mkdir -p "$writedir" 2>/dev/null; then
    echo "Error: Could not create directory $writedir"
    exit 1
fi

# Create/overwrite the file with the specified content
if ! echo "$writestr" > "$writefile" 2>/dev/null; then
    echo "Error: Could not create file $writefile"
    exit 1
fi

echo "File $writefile created successfully with content: $writestr"
