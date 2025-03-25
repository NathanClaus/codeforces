#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <prefix>"
    exit 1
fi

prefix=$1

# Find the C++ source file
cpp_file=$(find . -type f -name "${prefix}*.cpp" | head -n 1)

if [ -z "$cpp_file" ]; then
    echo "No C++ file found with prefix ${prefix}"
    exit 1
fi

echo "Found source file: ${cpp_file}"

# Get the directory of the source file
src_dir=$(dirname "${cpp_file}")

# Compile the C++ file
g++ -std=c++17 "${cpp_file}" -o A.exe

if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

echo "Compilation successful"

# Find the input file
input_file=$(find . -type f -name "${prefix}*.in" | head -n 1)
output_file="${src_dir}/${prefix}_testrun.out"

if [ -z "$input_file" ]; then
    echo "No input file found with prefix ${prefix}"
    echo "Running program without input file..."
    ./A.exe > "${output_file}"
else
    echo "Found input file: ${input_file}"
    echo "Running program with input file..."
    ./A.exe < "${input_file}" > "${output_file}"
fi

# Find and compare with answer file
answer_file=$(find . -type f -name "${prefix}.ans" | head -n 1)

if [ -z "$answer_file" ]; then
    echo "No answer file found with name ${prefix}.ans"
    echo "Output has been written to ${output_file}"
else
    echo "Found answer file: ${answer_file}"
    echo "Comparing output with answer file..."
    
    # Normalize both files by removing carriage returns and empty lines
    tr -d '\r' < "${output_file}" | grep -v '^$' > "${output_file}.tmp"
    tr -d '\r' < "${answer_file}" | grep -v '^$' > "${answer_file}.tmp"
    
    # Get line counts
    output_lines=$(wc -l < "${output_file}.tmp")
    answer_lines=$(wc -l < "${answer_file}.tmp")
    
    # Compare normalized files
    diff_output=$(diff -w -B "${output_file}.tmp" "${answer_file}.tmp")
    if [ $? -eq 0 ]; then
        echo "All ${answer_lines} lines match perfectly! ✓"
    else
        # Count different lines more accurately
        different_lines=$(diff -y --suppress-common-lines "${output_file}.tmp" "${answer_file}.tmp" | wc -l)
        matching_lines=$((answer_lines - different_lines))
        echo "Results:"
        echo "- Matching lines: ${matching_lines}"
        echo "- Different lines: ${different_lines}"
        echo "- Expected lines: ${answer_lines}"
        echo "- Your output lines: ${output_lines}"
        
        echo -e "\nFirst few differences:"
        echo "Line#  Your Output                 | Expected Output"
        echo "------------------------------------------------"
        diff "${output_file}.tmp" "${answer_file}.tmp" | grep "^[0-9c]" | while read -r lineinfo; do
            line_num=$(echo "$lineinfo" | cut -d"c" -f1)
            your_output=$(sed -n "${line_num}p" "${output_file}.tmp")
            expected_output=$(sed -n "${line_num}p" "${answer_file}.tmp")
            printf "%-6s: %-25s | %s\n" "$line_num" "$your_output" "$expected_output"
        done | head -n 5
    fi
    
    # Clean up temporary files
    rm "${output_file}.tmp" "${answer_file}.tmp"
fi 