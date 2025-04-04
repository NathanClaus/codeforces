#!/bin/bash

# Check if correct number of arguments are provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <contest_number> <problem_letter>"
    echo "Example: $0 2090 B"
    exit 1
fi

CONTEST_NUM=$1
PROBLEM_LETTER=$2

# Convert problem letter to uppercase
PROBLEM_LETTER=$(echo $PROBLEM_LETTER | tr '[:lower:]' '[:upper:]')

# Create contest directory if it doesn't exist
CONTEST_DIR="contests/$CONTEST_NUM"
mkdir -p "$CONTEST_DIR/input"

# Copy template to new problem file
cp codeforces_base_template.cpp "$CONTEST_DIR/${CONTEST_NUM}${PROBLEM_LETTER}.cpp"

# Create empty input and answer files
touch "$CONTEST_DIR/input/${CONTEST_NUM}${PROBLEM_LETTER}.in"
touch "$CONTEST_DIR/input/${CONTEST_NUM}${PROBLEM_LETTER}.ans"

echo "Created files:"
echo "- $CONTEST_DIR/${CONTEST_NUM}${PROBLEM_LETTER}.cpp"
echo "- $CONTEST_DIR/input/${CONTEST_NUM}${PROBLEM_LETTER}.in"
echo "- $CONTEST_DIR/input/${CONTEST_NUM}${PROBLEM_LETTER}.ans" 