/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:55:45 by maiman-m          #+#    #+#             */
/*   Updated: 2024/07/24 16:52:23 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_one.hh"

#ifndef RPN_HPP
#define RPN_HPP

class RPN
{
public:
	static void parse_notation(std::string expr);
	static void calculation(char op);

private:
	RPN();
	RPN(const RPN &rhs);
	RPN &operator=(const RPN &rhs);
	~RPN();

	static std::stack<int> notation_;

};

#endif
