/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:47:09 by maiman-m          #+#    #+#             */
/*   Updated: 2024/07/24 00:35:02 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_one.hh"

/* ============================================================================== */
/* 								error handling									  */
/* ============================================================================== */

/* ============================================================================== */
/* 								display											  */
/* ============================================================================== */

// queue fifo
// program name	: RPN
// program arg	: inverted polish maths expression
	// digits		: < 10
	// operations	: +, -, /, *
	// note			: no parentheses and decimals
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		FORMAT_ERR("Digits must be `int`s less than `10`.");
		FORMAT_ERR("Only +, -, /, * operations.");
		return (FORMAT_ERR("Usage: ./RPN [Reverse Polish Notation]"), 1);
	}

	RPN::parse_notation(argv[1]);

	return (0);
}
