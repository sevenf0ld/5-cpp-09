#!/bin/bash

red='\033[0;31m'
green='\033[0;33m'
blue='\033[0;34m'
none='\033[m'

# create an array of cmd inv arguments
args=(
	"input_valid_1.txt"
	"input_valid_2.txt"
	"input_valid_3.txt"

	"input_inv_2.txt"
	"input_inv_3.txt"
	"input_inv_4.txt"
	"input_inv_5.txt"
	"input_inv_6.txt"
	"input_inv_7.txt"
	"input_inv_8.txt"
	"input_inv_9.txt"
	"input_inv_10.txt"
	"input_inv_11.txt"
	"input_inv_12.txt"

	"input_val_3.txt"
	"input_val_4.txt"
	"input_val_5.txt"
	"input_val_6.txt"
	"input_val_7.txt"
	"input_val_8.txt"

	"input_date_4.txt"
	"input_date_5.txt"
	"input_date_6.txt"
	"input_date_7.txt"
	"input_date_8.txt"
	"input_date_9.txt"
	"input_date_10.txt"
	"input_date_11.txt"
	"input_date_12.txt"
	"input_date_13.txt"
	"input_date_14.txt"
	"input_date_15.txt"
	"input_date_16.txt"
	"input_date_17.txt"
	"input_date_18.txt"
	"input_date_19.txt"
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
