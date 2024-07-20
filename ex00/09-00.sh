#!/bin/bash

red='\033[0;31m'
green='\033[0;33m'
blue='\033[0;34m'
none='\033[m'

# create an array of cmd line arguments
args=(
	"input_valid_1.txt"
	"input_valid_2.txt"
	"input_valid_3.txt"

	"input_line_2.txt"
	"input_line_3.txt"
	"input_line_4.txt"
	"input_line_5.txt"
	"input_line_6.txt"
	"input_line_7.txt"
	"input_line_8.txt"
	"input_line_9.txt"
	"input_line_10.txt"
	"input_line_11.txt"
	"input_line_12.txt"

	"input_val_3.txt"
	"input_val_4.txt"
	"input_val_5.txt"
	"input_val_6.txt"
	"input_val_7.txt"
	"input_val_8.txt"
	)

# create a variable with the name of the executable
exe="./btc"

# set -e

# specify name of Makefile
# make re -f Makefile
make re --silent

reset

for arg in "${args[@]}"; do
    echo -e "$blue $exe $arg: $none"
    ./"$exe" "$arg"
done

make fclean -s
