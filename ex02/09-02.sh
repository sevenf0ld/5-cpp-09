#!/bin/bash

red='\033[0;31m'
green='\033[0;33m'
blue='\033[0;34m'
none='\033[m'

# create an array of cmd inv arguments
args=(
	# ============================================================================== #
	# 									non-integer									 #
	# ============================================================================== #
	"100.0 2000 30000.0"
	"9 8 7 inf"
	# ============================================================================== #
	# 									negative									 #
	# ============================================================================== #
	"-2 3 4"
	# ============================================================================== #
	# 									duplicate									 #
	# ============================================================================== #
	"1 1 2 3"
	"10 20 30 40 40"
	"90 80 70 90"
	"111 222 333 444 444 555 666"
	# ============================================================================== #
	# 									sorted										 #
	# ============================================================================== #
	"100 200 300 400 500"
	# ============================================================================== #
	# 								leading signs									 #
	# ============================================================================== #
	"+2 1 3"
	"++3 1 2"
	"4 5 --6"
	# ============================================================================== #
	# 								trailing signs									 #
	# ============================================================================== #
	"2+ 1 3"
	"3++ 1 2"
	"4 5 6--"
	# ============================================================================== #
	# 									alphabets									 #
	# ============================================================================== #
	"1 2 3 a"
	"4b 5 6"
	"7 8 c9"
	"10 d11d 12"
	# ============================================================================== #
	# 									symbols										 #
	# ============================================================================== #
	"1 2 3 4 5 6 #"
	"@ $ ^ * )"
	"2^2 5 6"
	"3! 4 5"
	# ============================================================================== #
	# 								valid (subject)						 			 #
	# ============================================================================== #
	"3 5 9 7 4"
	#'shuf -i 1-100000 -n 3000 | tr "\n" " "'
	# ============================================================================== #
	# 								valid (eval sheet)								 #
	# ============================================================================== #
	#'shuf -i 1-1000 -n 3000 | tr "\n" " " '
	"10 9 8 7 6 5 4 3 2 1"
	"9000 7000 5000 3000 1000"
	# ============================================================================== #
	# 									valid (self)								 #
	# ============================================================================== #
	"10 100 20 200 3 97 99 21"
	"4 5 6 7 8 9 0 1 2 3"
	)

# create a variable with the name of the executable
exe="./PmergeMe"

# set -e

# specify name of Makefile
# make re -f Makefile
make re --silent

reset

for arg in "${args[@]}"; do
    echo -e "$blue $exe $arg: $none"
    ./"$exe" $arg
done

make fclean -s
