/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:47:09 by maiman-m          #+#    #+#             */
/*   Updated: 2024/07/24 19:05:41 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_one.hh"

/* ============================================================================== */
/* 								error handling									  */
/* ============================================================================== */
void validate_notation(std::string expr)
{
	if (expr.find_first_not_of("0123456789+-/* ") != std::string::npos
			|| expr.find_first_not_of(" ") == std::string::npos
			|| expr.find_first_not_of("0123456789 ") == std::string::npos
			|| expr.find_first_not_of("+-/* ") == std::string::npos)
	{
		FORMAT_ERR("Only integers (0, 9) and operations {+, -, /, *} allowed.");
		exit(EXIT_FAILURE);
	}

	std::stringstream expr_stream(expr);
	std::string token;
	std::stack<int> tmp;
	while (std::getline(expr_stream, token, ' '))
	{
		if (token.find_first_not_of("0123456789") == std::string::npos)
		{
			int num = atoi(token.c_str());
			if (num > 9)
			{
				FORMAT_ERR("Ints must be less than 10.");
				exit(EXIT_FAILURE);
			}
			tmp.push(num);
		}
		else if (token.find_first_not_of("+-/*") == std::string::npos)
		{
			if (tmp.size() < 2)
			{
				FORMAT_ERR("Invalid notation.");
				exit(EXIT_FAILURE);
			}
			tmp.pop();
			tmp.pop();
			tmp.push(1);
		}
		else
		{
			FORMAT_ERR("Invalid notation.");
			exit(EXIT_FAILURE);
		}
	}
	if (tmp.size() != 1)
	{
		FORMAT_ERR("Invalid notation.");
		exit(EXIT_FAILURE);
	}
}

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
		FORMAT_ERR("Only integers (0, 9) and operations {+, -, /, *} allowed.");
		return (FORMAT_ERR("Usage: ./RPN [Reverse Polish Notation]"), 1);
	}

	validate_notation(argv[1]);
	RPN::parse_notation(argv[1]);

	return (0);
}
