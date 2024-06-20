#!/bin/bash

# Check if fzf is installed
if ! command -v fzf &> /dev/null; then
    echo "fzf is not installed. Please install it first."
    exit 1
fi

# Function to search and display context
search_and_display() {
    local query="$1"
    grep -rl --context=5 "$query" . | fzf +m --bind "ctrl-t:preview-context"
}

# Prompt user for input
read -p "Enter a string to search: " searchString

# Call the function and display results
search_and_display "$searchString"

