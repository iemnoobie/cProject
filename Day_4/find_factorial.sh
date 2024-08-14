#!/bin/bash

# Prompt the user to enter a number
read -p "Enter a number: " number

# Check if the input is a valid non-negative integer
if ! [[ "$number" =~ ^[0-9]+$ ]]; then
    echo "Invalid input. Please enter a non-negative integer."
    exit 1
fi

# Initialize factorial result to 1
factorial=1

# Calculate factorial using a loop
for (( i=1; i<=number; i++ )); do
    factorial=$(( factorial * i ))
done

# Output the result
echo "Factorial of $number is $factorial."

