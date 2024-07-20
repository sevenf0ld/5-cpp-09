/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:45:38 by maiman-m          #+#    #+#             */
/*   Updated: 2024/07/20 14:29:45 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_zero.hh"

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
		int	num = 0;
		while (std::getline(line_stream, token, '|'))
		{
			if (token.find_first_not_of(' ') == std::string::npos)
				return (FORMAT_ERR("\'" + line + "\'" + " not in line with the format `date | value`: < 2 tokens or all spaces for either"), FALSE);
			num++;
		}
		if (num != 2)
			return (FORMAT_ERR("\'" + line + "\'" + " not in line with the format `date | value`: < 2 tokens or all spaces for either"), FALSE);

		std::getline(db_file, line);
	}

	return (TRUE);
}

int	err_free_value(char *database)
{
	std::ifstream	db_file(database);
	if (!db_file)
	{
		FORMAT_ERR("Failed to open " + std::string(database));
		return (FALSE);
	}

	std::string	line;
	std::size_t	found;

	// skip date | value on the first line
	std::getline(db_file, line);
	std::getline(db_file, line);
	while (db_file.good())
	{
		found = line.find("|");
		if (found == std::string::npos)
			return (FORMAT_ERR("\'" + line + "\'" + " not in line with the format `date | value`: no delim"), FALSE);
	
		std::string value = line.substr(found + 1);
		// non-digits are converted to 
		double	val = std::strtod(value.c_str(), NULL);
		if (!(val > 0 && val < 100))
			return (FORMAT_ERR("\'" + line + "\'" + " not in line with the value format `(0, 100)`"), FALSE);

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
	//if (err_free_date(argv[1]) == FALSE)
	//	return (1);
	if (err_free_value(argv[1]) == FALSE)
		return (1);

	return (0);
}
