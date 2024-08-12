/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:38:55 by maiman-m          #+#    #+#             */
/*   Updated: 2024/08/12 14:25:03 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_two.hh"

/* ============================================================================== */
/* 								error handling									  */
/* ============================================================================== */
static int err_free_count(int count)
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

static int positive_int_seq(std::string seq)
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
/* 									display										  */
/* ============================================================================== */
static void print_elapsed_time(struct timespec start, struct timespec end, size_t n, std::string container_type)
{
	double diff =  (end.tv_sec - start.tv_sec) * (1e6) + (end.tv_nsec - start.tv_nsec) * (1e-3);
	std::cout << AC_BOLD << "Time to process a range of " << n << " elements with "
			  << container_type << "	:	" << AC_NORMAL
			  << std::fixed << std::setprecision(5) << diff << " µs" << std::endl;
	std::cout << std::endl;
}

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

	for (int i = 1; argv[i] != NULL; i++)
	{
		if (!positive_int_seq(argv[i]))
			return (1);
	}

	std::deque<int> tmp;
	for (int i = 1; argv[i] != NULL; i++)
		tmp.push_back(atoi(argv[i]));
	if (!no_dup_seq(tmp) || is_sorted_seq(tmp))
		return (1);
	tmp.clear();

	struct timespec start;
	struct timespec end;

/* ============================================================================== */
/* 										vector									  */
/* 								data management & sorting						  */
/* ============================================================================== */
	FORMAT_TEST("VECTOR");

	clock_gettime(CLOCK_MONOTONIC_RAW, &start);

	std::vector<int> vec;
	for (int i = 1; argv[i] != NULL; i++)
		vec.push_back(atoi(argv[i]));
	std::vector<int> vec_old(vec);
	//try
	//{
	//	no_dup_seq(vec);
	//	is_sorted_seq(vec);

	//	PmergeMe::ford_johnson_sort(vec);

	//	clock_gettime(CLOCK_MONOTONIC_RAW, &end);

	//	std::cout << "Before	:	";
	//	std::copy(vec_old.begin(), vec_old.end(), std::ostream_iterator<int>(std::cout, " "));
	//	std::cout << std::endl;

	//	std::cout << "After	:	";
	//	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	//	std::cout << std::endl;

	//	print_elapsed_time(start, end, vec.size(), "std::vector");
	//}
	//catch (const std::invalid_argument &e)
	//{
	//	EXCEPTION_MSG(e.what());
	//}
	PmergeMe::ford_johnson_sort(vec);

	clock_gettime(CLOCK_MONOTONIC_RAW, &end);

	std::cout << "Before	:	";
	std::copy(vec_old.begin(), vec_old.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	std::cout << "After	:	";
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	print_elapsed_time(start, end, vec.size(), "std::vector");


/* ============================================================================== */
/* 										deque									  */
/* 								data management & sorting						  */
/* ============================================================================== */
	FORMAT_TEST("DEQUE");

	clock_gettime(CLOCK_MONOTONIC_RAW, &start);

	std::deque<int> deq;
	for (int i = 1; argv[i] != NULL; i++)
		deq.push_back(atoi(argv[i]));
	std::deque<int> deq_old(deq);
	//try
	//{
	//	no_dup_seq(deq);
	//	is_sorted_seq(deq);

	//	PmergeMe::ford_johnson_sort(deq);

	//	clock_gettime(CLOCK_MONOTONIC_RAW, &end);

	//	std::cout << "Before	:	";
	//	std::copy(deq_old.begin(), deq_old.end(), std::ostream_iterator<int>(std::cout, " "));
	//	std::cout << std::endl;

	//	std::cout << "After	:	";
	//	std::copy(deq.begin(), deq.end(), std::ostream_iterator<int>(std::cout, " "));
	//	std::cout << std::endl;

	//	print_elapsed_time(start, end, deq.size(), "std::deque");
	//}
	//catch (const std::invalid_argument &e)
	//{
	//	EXCEPTION_MSG(e.what());
	//}
	PmergeMe::ford_johnson_sort(deq);

	clock_gettime(CLOCK_MONOTONIC_RAW, &end);

	std::cout << "Before	:	";
	std::copy(deq_old.begin(), deq_old.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	std::cout << "After	:	";
	std::copy(deq.begin(), deq.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	print_elapsed_time(start, end, deq.size(), "std::deque");

/* ============================================================================== */
/* 										list									  */
/* 								data management & sorting						  */
/* ============================================================================== */
	FORMAT_TEST("LIST");

	clock_gettime(CLOCK_MONOTONIC_RAW, &start);

	std::list<int> lst;
	for (int i = 1; argv[i] != NULL; i++)
		lst.push_back(atoi(argv[i]));
	std::list<int> lst_old(lst);
	//try
	//{
	//	no_dup_seq(lst_old);
	//	is_sorted_seq(lst_old);

	//	PmergeMe::ford_johnson_sort(lst);

	//	clock_gettime(CLOCK_MONOTONIC_RAW, &end);

	//	std::cout << "Before	:	";
	//	std::copy(lst_old.begin(), lst_old.end(), std::ostream_iterator<int>(std::cout, " "));
	//	std::cout << std::endl;

	//	std::cout << "After	:	";
	//	std::copy(lst.begin(), lst.end(), std::ostream_iterator<int>(std::cout, " "));
	//	std::cout << std::endl;

	//	print_elapsed_time(start, end, lst.size(), "std::list");
	//}
	//catch (const std::invalid_argument &e)
	//{
	//	EXCEPTION_MSG(e.what());
	//}
	PmergeMe::ford_johnson_sort(lst);

	clock_gettime(CLOCK_MONOTONIC_RAW, &end);

	std::cout << "Before	:	";
	std::copy(lst_old.begin(), lst_old.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	std::cout << "After	:	";
	std::copy(lst.begin(), lst.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	print_elapsed_time(start, end, lst.size(), "std::list");

	return (0);
}
