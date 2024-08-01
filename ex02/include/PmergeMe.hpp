/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:41:05 by maiman-m          #+#    #+#             */
/*   Updated: 2024/08/01 18:55:41 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_two.hh"

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

// Ford-Johnson merge insertion sort
// a combination of merge-sort and binary-search-insertion
// 1.	

// Jacobsthal number
// 0, 1 is the starting sequence given by the notation a, b
// the rest can be figured out
// 		1. a + a + b
// 		2. 2a + b
// 0, 1, 1, 3, 5, 11, 21, 43, 85, ...

// merge-sort
// 		1. recursively divides the list into half repeatedly until a single node is left
//		2. merge the smaller list back into the larger list in correct order
//			- unit length cell into sorted subarrays
//			- subarray into subarray

// binary-search-insertion
// 		1. create a new node
// 		2. if smaller, add to the left of the parent node
// 			if larger, add child to the right

class PmergeMe
{
public:

private:
};

#endif
