/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:39:08 by maiman-m          #+#    #+#             */
/*   Updated: 2024/08/10 15:26:39 by maiman-m         ###   ########.fr       */
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
	int staggler = c.back();
	if (is_odd(c))
		c.pop_back();
	else
		staggler = -1;
	(void) staggler;

	std::vector <int_pair> vec_pair = group_pairs< std::vector <int_pair > >(c);

	sort_descending(vec_pair);
	merge_sort(vec_pair);
	print_pair(vec_pair);

	std::vector<int> sorted_vec = create_sorted_seq< std::vector <int> >(vec_pair);
	std::copy(sorted_vec.begin(), sorted_vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	std::vector<int> pending = create_pend_seq< std::vector <int> >(vec_pair);
	std::copy(pending.begin(), pending.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

}

/* ============================================================================== */
/* 							static sort list member function					  */
/* ============================================================================== */
void PmergeMe::ford_johnson_sort(std::list<int> &c)
{
	int staggler = c.back();
	if (is_odd(c))
		c.pop_back();
	else
		staggler = -1;
	(void) staggler;

	std::list <int_pair> lst_pair = group_pairs< std::list <int_pair> >(c);

	sort_descending(lst_pair);
	merge_sort(lst_pair);
	print_pair(lst_pair);

	std::list<int> sorted_lst = create_sorted_seq< std::list <int> >(lst_pair);
	std::copy(sorted_lst.begin(), sorted_lst.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	std::list<int> pending = create_pend_seq< std::list <int> >(lst_pair);
	std::copy(pending.begin(), pending.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}
