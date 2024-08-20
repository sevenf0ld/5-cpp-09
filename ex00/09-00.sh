#!/bin/bash

red='\033[0;31m'
green='\033[0;33m'
blue='\033[0;34m'
none='\033[m'

# create an array of cmd inv arguments
line_args=(
	"input_line_1.txt"
	"input_line_2.txt"
)
inv_args=(
	"input_inv_2.txt"
	"input_inv_3.txt"
	"input_inv_4.txt"
	"input_inv_5.txt"
	"input_inv_6.txt"
	"input_inv_7.txt"
	"input_inv_8.txt"
	"input_inv_9.txt"
	"input_inv_10.txt"
)
val_args=(
	"input_val_3.txt"
	"input_val_4.txt"
	"input_val_5.txt"
	"input_val_6.txt"
	"input_val_7.txt"
	"input_val_8.txt"
)
date_args=(
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

#if [ $1 -eq "line" ];
if [ $1 -eq 0 ];
then
	for larg in "${line_args[@]}"; do
    	echo -e "$blue $exe $larg: $none"
    	./"$exe" "$larg"
	done
fi

#if [ $1 -eq "inv" ];
if [ $1 -eq 1 ];
then
	for iarg in "${inv_args[@]}"; do
		echo -e "$blue $exe $iarg: $none"
		./"$exe" "$iarg"
	done
fi

#if [ $1 -eq "val" ];
if [ $1 -eq 2 ];
then
	for varg in "${val_args[@]}"; do
		echo -e "$blue $exe $varg: $none"
		./"$exe" "$varg"
	done
fi

#if [ $1 -eq "date" ];
if [ $1 -eq 3 ];
then
	for darg in "${date_args[@]}"; do
		echo -e "$blue $exe $darg: $none"
		./"$exe" "$darg"
	done
fi

if [ $1 -eq 6 ];
then
	for larg in "${line_args[@]}"; do
    	echo -e "$blue $exe $larg: $none"
    	./"$exe" "$larg"
	done
	for iarg in "${inv_args[@]}"; do
		echo -e "$blue $exe $iarg: $none"
		./"$exe" "$iarg"
	done
	for varg in "${val_args[@]}"; do
		echo -e "$blue $exe $varg: $none"
		./"$exe" "$varg"
	done
	for darg in "${date_args[@]}"; do
		echo -e "$blue $exe $darg: $none"
		./"$exe" "$darg"
	done
fi

make fclean -s
