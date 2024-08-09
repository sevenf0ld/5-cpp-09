/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:39:08 by maiman-m          #+#    #+#             */
/*   Updated: 2024/08/10 00:59:02 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_two.hh"

/* ============================================================================== */
/* 								rule of three									  */
/* ============================================================================== */
PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &rhs)
{
	(void) rhs;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs)
{
	(void) rhs;
	return (*this);
}

PmergeMe::~PmergeMe()
{
}

/* ============================================================================== */
/* 							static sort vector member function					  */
/* ============================================================================== */
void PmergeMe::ford_johnson_sort(std::vector<int> &c)
{
	std::copy(c.begin(), c.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	int staggler = c.back();
	if (is_odd(c))
		c.pop_back();
	else
		staggler = -1;
	(void) staggler;
	std::vector <int_pair> vec_pair = create_pairs< std::vector <int_pair > >(c);
	print_pair(vec_pair);
}

/* ============================================================================== */
/* 							static sort list member function					  */
/* ============================================================================== */
void PmergeMe::ford_johnson_sort(std::list<int> &c)
{
	std::copy(c.begin(), c.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	int staggler = c.back();
	if (is_odd(c))
		c.pop_back();
	else
		staggler = -1;
	(void) staggler;
	std::list <int_pair> lst_pair = create_pairs< std::list <int_pair> >(c);
	print_pair(lst_pair);
}
