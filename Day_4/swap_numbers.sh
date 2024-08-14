#!/bin/bash

# Prompt the user to enter two numbers
read -p "Enter the first number: " num1
read -p "Enter the second number: " num2

# Check if the inputs are valid numbers
if ! [[ "$num1" =~ ^-?[0-9]+$ ]] || ! [[ "$num2" =~ ^-?[0-9]+$ ]]; then
    echo "Invalid input. Please enter valid numbers."
    exit 1
fi

# Swap the numbers using a temporary variable
temp=$num1
num1=$num2
num2=$temp

# Output the result
echo "After swapping: "
echo "First number: $num1"
echo "Second number: $num2"

