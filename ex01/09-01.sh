#!/bin/bash

red='\033[0;31m'
green='\033[0;33m'
blue='\033[0;34m'
none='\033[m'

# create an array of cmd inv arguments
args=(
	""
	" "
	"(1 + 1)"
	"1 + 1.0"
	"1"
	"*"
	"1 2 +"
	"8 9 * 9 - 9 - 9 - 4 - 1 +"
	"7 7 * 7 -"
	"1 2 * 2 / 2 * 2 4 - +"
	" 9 8 * 4 * 4 / 2 + 9 - 8 - 8 - 1 - 6 -"
	" 1 2 * 2 / 2 + 5 * 6 - 1 3 * - 4 5 * * 8 / "
	)

# create a variable with the name of the executable
exe="./RPN"

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
