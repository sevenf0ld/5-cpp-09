/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:29:17 by maiman-m          #+#    #+#             */
/*   Updated: 2024/07/24 16:28:06 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_one.hh"

//std::queue<int> RPN::notation_;
//std::queue<std::string> RPN::notation_;
std::stack<int> RPN::notation_;

/* ============================================================================== */
/* 								rule of three				  */
/* ============================================================================== */
RPN::RPN()
{
}

RPN::RPN(const RPN &rhs)
{
	(void) rhs;
}

RPN &RPN::operator=(const RPN &rhs)
{
	(void) rhs;
	return (*this);
}

RPN::~RPN()
{
}

/* ============================================================================== */
/* 							static parse member functions			  */
/* ============================================================================== */
// cant be operation leading
// cant be single operand leading
// separate validate and parse
// what if two operations stick together
// what if operands and operations stick together
void RPN::parse_notation(std::string expr)
{
	if (expr.find_first_not_of("0123456789+-/* ") != std::string::npos
			|| expr.empty()
			|| expr.find_first_not_of(" ") == std::string::npos
			|| expr.find_first_not_of("0123456789") == std::string::npos
			|| expr.find_first_not_of("+-/*") == std::string::npos)
	{
		FORMAT_ERR("Must have only integers (0, 9) and +, -, /, * operations.");
		return ;
	}

	std::stringstream expr_stream(expr);
	std::string token;
	while (std::getline(expr_stream, token, ' '))
	{
		if (token.find_first_not_of("0123456789") == std::string::npos)
		{
			notation_.push(atoi(token.c_str()));
			//std::cout << AC_MAGENTA << notation_.top() << AC_NORMAL << std::endl;
		}
		else if (token.find_first_not_of("+-/*") == std::string::npos)
		{
			calculation(token[0]);
			//std::cout << AC_CYAN << notation_.size() << AC_NORMAL << std::endl;
			;
		}
	}

	std::cout << AC_CYAN << notation_.top() << AC_NORMAL << std::endl;

}

// handle division by 0
void RPN::calculation(char op)
{
	int a;
	int b;

	b = notation_.top();
	notation_.pop();
	a = notation_.top();
	notation_.pop();
	switch (op)
	{
		case '+':
			//notation_.push(notation_.pop() + notation_.pop());
			notation_.push(a + b);
			break ;
		case '-':
			//notation_.push(notation_.pop() - notation_.pop());
			notation_.push(a - b);
			break ;
		case '/':
			//notation_.push(notation_.pop() / notation_.pop());
			if (b == 0)
			{
				FORMAT_ERR("Division by zero is not allowed.");
				exit(EXIT_FAILURE);
			}
			notation_.push(a / b);
			break ;
		case '*':
			//notation_.push(notation_.pop() * notation_.pop());
			notation_.push(a * b);
			break ;
	}
	(void) op;
}

/* ============================================================================== */
/* 								static getters				  */
/* ============================================================================== */

/* ============================================================================== */
/* 								static setters				  */
/* ============================================================================== */

/* ============================================================================== */
/* 									getters				  */
/* ============================================================================== */
