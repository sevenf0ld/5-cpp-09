/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:29:17 by maiman-m          #+#    #+#             */
/*   Updated: 2024/07/24 20:01:31 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_one.hh"

// std::queue<int> RPN::notation_;
// std::queue<std::string> RPN::notation_;
std::stack<int> RPN::notation_;

/* ============================================================================== */
/* 									rule of three				  				  */
/* ============================================================================== */
RPN::RPN()
{
}

RPN::RPN(const RPN &rhs)
{
	(void)rhs;
}

RPN &RPN::operator=(const RPN &rhs)
{
	(void)rhs;
	return (*this);
}

RPN::~RPN()
{
}

/* ============================================================================== */
/* 							static parse member function						  */
/* ============================================================================== */
void RPN::parse_notation(std::string expr)
{
	std::stringstream expr_stream(expr);
	std::string token;
	while (std::getline(expr_stream, token, ' '))
	{
		if (token.find_first_not_of("0123456789") == std::string::npos)
			notation_.push(atoi(token.c_str()));
		else if (token.find_first_not_of("+-/*") == std::string::npos)
			if (token.size() == 1)
				calculation(token[0]);
	}

	std::cout << AC_GREEN << notation_.top() << AC_NORMAL << std::endl;
}

/* ============================================================================== */
/* 							calculation member function							  */
/* ============================================================================== */
void RPN::calculation(char op)
{
	int b = notation_.top();
	notation_.pop();
	int a = notation_.top();
	notation_.pop();

	switch (op)
	{
	case '+':
		notation_.push(a + b);
		break;
	case '-':
		notation_.push(a - b);
		break;
	case '/':
		if (b == 0)
		{
			FORMAT_ERR("Division by zero is not allowed.");
			exit(EXIT_FAILURE);
		}
		notation_.push(a / b);
		break;
	case '*':
		notation_.push(a * b);
		break;
	}
}
