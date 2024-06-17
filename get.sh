#!/bin/bash

# Define the input file
input_file="tail.txt"

# Create an empty output file
output_file="output.txt"
> "$output_file"

# Read the input file line by line
while IFS= read -r line
do
    # Check if the line matches the pattern "=========="
    if [[ "$line" == "=========="* ]]; then
        # If it's the first "==========", it's the start of a new part
        if [[ -z $start ]]; then
            start=true
        else
            # If it's not the first "==========", it's the end of a part
            # Extract the content and append it to the output file
            echo "$content" >> "$output_file"
            content=""
        fi
    elif [[ ! -z $start ]]; then
        # If we are in the middle of a part, append the line to the content
        content+="$line\n"
    fi
done < "$input_file"

# Append the last part of content to the output file
echo "$content" >> "$output_file"

