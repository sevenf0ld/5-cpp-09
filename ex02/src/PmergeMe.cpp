/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:39:08 by maiman-m          #+#    #+#             */
/*   Updated: 2024/08/05 11:56:56 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_two.hh"

void PmergeMe::validate(std::string arg)
{
	std::stringstream arg_stream(arg);
	std::string token;
	while (std::getline(arg_stream, token, ' '))
	{
		// to check for non-digits
		size_t	invalid = token.find_first_not_of("0123456789");
		char *wrong;
		int64_t val = std::strtol(token.c_str(), &wrong, 10);
		if (invalid != std::string::npos)
		{
			// to allow valid leading postive or negative sign
			if (wrong != NULL && !(std::string(wrong)).empty())
			{
				//FORMAT_ERR("Non-digit found: " + std::string(wrong) + " in " + token.substr(invalid));
				FORMAT_ERR("Non-digit found: " + std::string(wrong));
				exit(EXIT_FAILURE);
			}
		}
		// to check for beyond INT_MIN and INT_MAX
		if (val < INT_MIN || val > INT_MAX)
		{
			FORMAT_ERR("Converted value is beyond int range.");
			exit(EXIT_FAILURE);
		}
		// to check for negative numbers
		if (val < 0)
		{
			std::ostringstream val_str;
			val_str << val;
			FORMAT_ERR("Negative value found: " + val_str.str());
			exit(EXIT_FAILURE);
		}
		// to check for duplicate
		// store in the respective containers first before calling sort & adjacent_find
	}
}
