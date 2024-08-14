#!/bin/bash

# Function to calculate the average
calculate_average() {
    local sum=$1
    local count=$2
    echo "scale=2; $sum / $count" | bc
}

# Prompt the user to enter the number of values
read -p "Enter the number of values (N): " N

# Check if the input is a valid positive integer
if ! [[ "$N" =~ ^[0-9]+$ ]] || [ "$N" -le 0 ]; then
    echo "Invalid input. Please enter a positive integer."
    exit 1
fi

# Initialize variables
largest=-INF
smallest=INF
sum=0

# Read N numbers and compute statistics
for (( i=1; i<=N; i++ )); do
    read -p "Enter number $i: " num

    # Check if the input is a valid number
    if ! [[ "$num" =~ ^-?[0-9]+$ ]]; then
        echo "Invalid input. Please enter a valid number."
        exit 1
    fi

    # Update largest and smallest
    if (( num > largest )); then
        largest=$num
    fi

    if (( num < smallest )); then
        smallest=$num
    fi

    # Update sum
    sum=$(( sum + num ))
done

# Calculate average
average=$(calculate_average $sum $N)

# Output the results
echo "Largest number: $largest"
echo "Smallest number: $smallest"
echo "Average: $average"

