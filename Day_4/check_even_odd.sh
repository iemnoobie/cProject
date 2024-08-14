#!/bin/bash

# Prompt the user to enter a number
read -p "Enter a number: " number

# Check if the input is a valid number
if ! [[ "$number" =~ ^-?[0-9]+$ ]]; then
    echo "Invalid input. Please enter a valid number."
    exit 1
fi

# Check if the number is even or odd
if (( number % 2 == 0 )); then
    echo "$number is even."
else
    echo "$number is odd."
fi

