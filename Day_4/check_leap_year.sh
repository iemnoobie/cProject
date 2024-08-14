#!/bin/bash

# Prompt the user to enter a year
read -p "Enter a year: " year

# Check if the input is a valid number
if ! [[ "$year" =~ ^[0-9]+$ ]]; then
    echo "Invalid input. Please enter a valid year."
    exit 1
fi

# Determine if the year is a leap year
if (( year % 400 == 0 )); then
    echo "$year is a leap year."
elif (( year % 100 == 0 )); then
    echo "$year is not a leap year."
elif (( year % 4 == 0 )); then
    echo "$year is a leap year."
else
    echo "$year is not a leap year."
fi

