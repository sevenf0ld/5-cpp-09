/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:38:55 by maiman-m          #+#    #+#             */
/*   Updated: 2024/08/07 12:24:23 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_two.hh"

/* ============================================================================== */
/* 								error handling									  */
/* ============================================================================== */
int err_free_count(int count)
{
	if (count == 1)
	{
		FORMAT_ERR("Usage: ./PmergeMe x x x x x x");
		return (FORMAT_ERR("Only non-duplicate positive integers as arguments are allowed."), FALSE);
	}
	if (count == 2)
	{
		FORMAT_ERR("Usage: ./PmergeMe x x x x x x");
		return (FORMAT_ERR("Arguments provided must be more than 1."), FALSE);
	}

	return (TRUE);
}

int positive_int_seq(std::string seq)
{
	std::stringstream seq_stream(seq);
	std::string token;
	while (std::getline(seq_stream, token, ' '))
	{
		// to check for non-digits
		size_t	invalid = token.find_first_not_of("0123456789");
		char *wrong;
		int64_t val = std::strtol(token.c_str(), &wrong, 10);
		if (invalid != std::string::npos)
		{
			// to allow valid leading postive or negative sign
			if (wrong != NULL && !(std::string(wrong)).empty())
				//FORMAT_ERR("Non-digit found: " + std::string(wrong) + " in " + token.substr(invalid));
				return (FORMAT_ERR("Non-digit found: " + std::string(wrong)), FALSE);
		}
		// to check for beyond INT_MIN and INT_MAX
		if (val < INT_MIN || val > INT_MAX)
			return (FORMAT_ERR("Converted value is beyond int range."), FALSE);
		// to check for negative numbers
		if (val < 0)
		{
			std::ostringstream val_strm;
			val_strm << val;
			return (FORMAT_ERR("Negative value found: " + val_strm.str()), FALSE);
		}
		// to check for duplicate
		// store in the respective containers first before calling sort & adjacent_find
	}
	return (TRUE);
}

/* ============================================================================== */
/* 								display											  */
/* ============================================================================== */

// sequments to program:
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
	if (!err_free_count(argc))
		return (1);

	std::deque<int> unsorted;
	for (int i = 1; argv[i] != NULL; i++)
	{
		if (!positive_int_seq(argv[i]))
			return (1);
		unsorted.push_back(atoi(argv[i]));
	}
	if (!no_dup_seq(unsorted) || is_sorted_seq(unsorted))
		return (1);

	std::vector<int> vec(unsorted.begin(), unsorted.end());
	std::list<int> lst(unsorted.begin(), unsorted.end());
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
	std::copy(lst.begin(), lst.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	return (0);
}
