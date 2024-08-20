/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:45:38 by maiman-m          #+#    #+#             */
/*   Updated: 2024/08/20 15:55:08 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_zero.hh"

/* ============================================================================== */
/* 								error handling									  */
/* ============================================================================== */
int err_free_arg(char **argv, int argc)
{
	if (argc != 2)
		return (FALSE);

	std::string database = argv[1];
	std::size_t found = database.find(".txt");
	if (found == std::string::npos)
		return (FALSE);

	std::string ext = database.substr(found);
	if (ext.compare(".txt") != 0)
		return (FALSE);

	return (TRUE);
}

std::string trim_str(std::string &str)
{

	std::size_t start = str.find_first_not_of(" ");
	std::size_t end = str.find_last_not_of(" ");
	if (start == std::string::npos || end == std::string::npos)
		return ("");

	std::string ret = str.substr(start, end - start + 1);
	return (ret);
}

/* ============================================================================== */
/* 										display									  */
/* ============================================================================== */
std::ostream &operator<<(std::ostream &out_stream, const std::map<std::string, float>::iterator &ite)
{
	float value = BitcoinExchange::get_value();
	out_stream << ite->first << " => " << value << " = " << ite->second * value << std::endl;
	return (out_stream);
}

// output the value of a certain amount of btc on a given date
// use the previous/lesser date if given a nonexistent date
// database is in csv format (provided)
// program param: a database which stores the different prices & dates to be evaluated
// a file, format unspecified, subject example is .txt)
// line		: "date | value"
// date		: "Y-M-D"
// valid	: float/+ve int & (0, 1000)
// use at least one std container
// said container must not be reused in later exercises in this module
// handle errors with appropriate msgs
int main(int argc, char **argv)
{
	if (err_free_arg(argv, argc) == FALSE)
		return (FORMAT_ERR("Usage: ./btc [filename].txt"), 1);

	BitcoinExchange::parse_database();
	BitcoinExchange::parse_input(argv[1]);

	return (0);
}
