/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:45:38 by maiman-m          #+#    #+#             */
/*   Updated: 2024/07/23 16:31:06 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_zero.hh"

std::ostream &operator<<(std::ostream &out_stream, const BitcoinExchange &rhs)
{
	std::map<std::string, float> dict;

	dict = rhs.get_btc_rate();

	for (std::map<std::string, float>::iterator ite = dict.begin(); ite != dict.end(); ite++)
		out_stream << ite->first << ": " << ite->second << std::endl;
	return (out_stream);
}

static int	err_free_arg(char **argv, int argc)
{
	if (argc != 2)
		return (FALSE);

	std::string	database = argv[1];

	std::size_t found = database.find(".txt");
	if (found == std::string::npos)
		return (FALSE);
	std::string ext = database.substr(found);
	if (ext.compare(".txt") != 0)
		return (FALSE);

	return (TRUE);
}

static int	is_leap_year(int yr)
{
	if (yr % 400 == 0)
		return (TRUE);
	else if (yr % 100 == 0)
		return (FALSE);
	else if (yr % 4 == 0)
		return (TRUE);
	return (FALSE);
}

int	err_free_date(tm conv)
{
	if (is_leap_year(conv.tm_year + 1900) == FALSE)
		if (conv.tm_mon + 1 == 2 && conv.tm_mday > 28)
			return (FORMAT_ERR("Only 28 days in Feb for non-leap years."), FALSE);

	if ((conv.tm_mon + 1 == 4 || conv.tm_mon + 1 == 6 || conv.tm_mon + 1 == 9 || conv.tm_mon + 1 == 11) && conv.tm_mday > 30)
		return (FORMAT_ERR("Only 30 days in Apr, Jun, Sept and Nov."), FALSE);

	return (TRUE);
}

int	validate_value(std::string value, double *v)
{
	float	val = std::strtof(value.c_str(), NULL);
	if (!(val > 0.0f && val < 100.0f))
		return (FORMAT_ERR("\'" + value + "\'" + " not in line with the value format `(0, 100)`"), FALSE);

	*v = val;
	return (TRUE);
}

std::string	trim_str(std::string &str)
{
	std::string	ret;

	std::size_t	start = str.find_first_not_of(" ");
	std::size_t	end = str.find_last_not_of(" ");
	if (start == std::string::npos || end == std::string::npos)
		return (ret);
	ret = str.substr(start, end - start + 1);
	return (ret);
}

// output the value of a certain amount of btc on a given date
	// use the previous/lesser date if given a nonexistent date
// database is in csv format (provided)
// program param: a database which stores the different prices & dates to be evaluated
	// a file, format unspecified, subject example is .txt)
	// line		: "date | value"
	// date		: "Y-M-D"
	// valid	: float/+ve int & (0, 100)
// use at least one std container
	// said container must not be reused in later exercises in this module
// handle errors with appropriate msgs
int	main(int argc, char **argv)
{
	if (err_free_arg(argv, argc) == FALSE)
		return (FORMAT_ERR("Usage: ./btc [filename].txt"), 1);

	BitcoinExchange::parse_database();
	BitcoinExchange::parse_input(argv[1]);

	return (0);
}
