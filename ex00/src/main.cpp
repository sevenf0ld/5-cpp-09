/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:45:38 by maiman-m          #+#    #+#             */
/*   Updated: 2024/07/21 13:12:47 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_zero.hh"

// Boost's trim is not allowed
// c++ regex library is not allowed
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

int	err_free_date(std::string date)
{
	std::stringstream	date_stream(date);
	std::string	token;
	int	num = 0;
	while (std::getline(date_stream, token, '-'))
	{
		if (token.find_first_not_of(" ") == std::string::npos)
			return (FORMAT_ERR("\'" + date + "\'" + " not in line with the date format `YYYY-MM-DD`: < 3 tokens or all spaces for either"), FALSE);
		if (num == 0 && token.size() != 4)
			return (FORMAT_ERR("\'" + date + "\'" + " not in line with the date format `YYYY-MM-DD`: YEAR"), FALSE);
		if (num == 1 && token.size() != 2)
			return (FORMAT_ERR("\'" + date + "\'" + " not in line with the date format `YYYY-MM-DD`: MONTH"), FALSE);
		if (num == 2 && token.size() != 2)
			return (FORMAT_ERR("\'" + date + "\'" + " not in line with the date format `YYYY-MM-DD`: DATE"), FALSE);
		num++;
	}
	if (num != 3)
		return (FORMAT_ERR("\'" + date + "\'" + " not in line with the date format `Y-M-D`: no delim"), FALSE);
	return (TRUE);
}

int	err_free_value(std::string value)
{
	// non-digits are converted to 0
	double	val = std::strtod(value.c_str(), NULL);
	if (!(val > 0 && val < 100))
		return (FORMAT_ERR("\'" + value + "\'" + " not in line with the value format `(0, 100)`"), FALSE);
	return (TRUE);
}

int	err_free_arg(char **argv, int argc)
{
	if (argc != 2)
		return (FALSE);

	std::string	database = argv[1];

	std::size_t found = database.find(".txt");
	if (found == std::string::npos)
		return (FALSE);
	std::string ext = database.substr(found);
	/*
	try
	{
		size_t	database_size = database.size();
		ext = database.substr(database_size - 4);
	}
	catch (std::out_of_range &e)
		return (FALSE);
	*/
	// c++20 allows ends_with
	if (ext.compare(".txt") != 0)
		return (FALSE);

	return (TRUE);
}

int	err_free_line(char *database)
{
	std::ifstream	db_file(database);
	if (!db_file)
	{
		FORMAT_ERR("Failed to open " + std::string(database));
		return (FALSE);
	}

	std::string	line;
	std::size_t	found;
	int	num_header_d = 0;
	int	num_header_v = 0;

	std::getline(db_file, line);
	while (db_file.good())
	{
		found = line.find("|");
		std::size_t	r_found = line.rfind("|");
		if (found == std::string::npos || r_found == std::string::npos)
			return (FORMAT_ERR("\'" + line + "\'" + " not in line with the format `date | value`: no delim"), FALSE);
		if (found != r_found)
			return (FORMAT_ERR("\'" + line + "\'" + "not in line with the format `date | value`: multi delims"), FALSE);

		std::stringstream	line_stream(line);
		std::string	token;
		int	num_pipe = 0;
		while (std::getline(line_stream, token, '|'))
		{
			if (token.find_first_not_of(" ") == std::string::npos)
				return (FORMAT_ERR("\'" + line + "\'" + " not in line with the format `date | value`: < 2 tokens or all spaces for either"), FALSE);

			std::string	trimmed_token = trim_str(token);
			if (!trimmed_token.compare("date"))
				num_header_d += 1;
			else
				if (num_pipe == 0)
					err_free_date(trimmed_token);
			if (!trimmed_token.compare("value"))
				num_header_v += 1;
			else
				if (num_pipe == 1)
					err_free_value(trimmed_token);
			//if (trimmed_token.find_first_not_of("-") != std::string::npos)
			//	err_free_date(trimmed_token);
			//if (trimmed_token.find_first_not_of("1234567890.") != std::string::npos)
			//	err_free_value(trimmed_token);

			num_pipe++;
		}

		if (num_header_d != 1 || num_header_v != 1)
			return (FORMAT_ERR("not in line with the file format: multiple header dates or values"), FALSE);
		if (num_pipe != 2)
			return (FORMAT_ERR("\'" + line + "\'" + " not in line with the format `date | value`: < 2 tokens or all spaces for either"), FALSE);

		std::getline(db_file, line);
	}

	return (TRUE);
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
	if (err_free_line(argv[1]) == FALSE)
		return (1);

	return (0);
}
