#!/bin/sh
# Basic finder.sh script for testing finder-test.sh
# Takes directory and search string as arguments
# Returns count of files and matching lines

if [ $# -ne 2 ]; then
    echo "Usage: $0 <directory> <search_string>"
    exit 1
fi

FILESDIR="$1"
SEARCHSTR="$2"

# Check if directory exists
if [ ! -d "$FILESDIR" ]; then
    echo "Directory $FILESDIR does not exist"
    exit 1
fi

# Count files in directory
NUMFILES=$(find "$FILESDIR" -type f | wc -l)

# Count matching lines
NUMMATCHING=$(grep -r "$SEARCHSTR" "$FILESDIR" 2>/dev/null | wc -l)

echo "The number of files are ${NUMFILES} and the number of matching lines are ${NUMMATCHING}"