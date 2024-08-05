/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:38:55 by maiman-m          #+#    #+#             */
/*   Updated: 2024/08/05 12:18:19 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_two.hh"

// arguments to program:
// 		- can be 1 or more
// 		- must be positive
// 		- must be integer
// 		- must handle 3000 different ints at the minimum
// display error messages
// use two containers (map & stack no longer usable)
// 		- the algorithm must be separated and not used as a generic function for both containers
// algorithm: Ford-Johnson merge insertion sort
// cout information (in order):
// 		- unsorted sequence
//		- sorted sequence
//		- duration of the algorithm by first sorting container
//		- duration of the algorithm by second sorting container
// duration must be precise (subject pdf uses microseconds)
// 		- sorting
// 		- data management
//
// VAGUE: "The management of errors related to duplicates is left to your discretion."
//
// alt: vector, deque, list
// 		- vector: can only add and remove to/from the back
// 		- deque & list: can add and remove to/from the front and back

// validate integer
// validate positive
// validate non-duplicate

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		FORMAT_ERR("Usage: ./PmergeMe x x x x x x");
		FORMAT_ERR("Usage: ./PmergeMe \"x x x x x x\"");
		return (FORMAT_ERR("Only non-duplicate positive integers as arguments are allowed."), 1);
	}
	for (int i = 1; argv[i] != NULL; i++)
		PmergeMe::validate(argv[i]);
}
