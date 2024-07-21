/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:45:38 by maiman-m          #+#    #+#             */
/*   Updated: 2024/07/21 17:47:14 by maiman-m         ###   ########.fr       */
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

int	validate_ymd(std::string token, char flag)
{
	int	digit = atoi(token.c_str());


	if (flag == 'Y')
	{
		if (token.size() != 4)
			return (FORMAT_ERR("\'" + token + "\'" + " not in line with the date format `YYYY`"), FALSE);
	}
	else if (flag == 'M')
	{
		if (token.size() != 2)
			return (FORMAT_ERR("\'" + token + "\'" + " not in line with the date format `MM`"), FALSE);
		if (digit < 1 || digit > 12)
			return (FORMAT_ERR("12 months max in a year."), FALSE);
	}
	else if (flag == 'D')
	{
		if (token.size() != 2)
			return (FORMAT_ERR("\'" + token + "\'" + " not in line with the date format `DD`"), FALSE);
		if (digit < 1 || digit > 31)
			return (FORMAT_ERR("31 days max in a month."), FALSE);
	}

	return (TRUE);
}

int	is_leap_year(int yr)
{
	if (yr % 400 == 0)
		return (TRUE);
	else if (yr % 100 == 0)
		return (FALSE);
	else if (yr % 4 == 0)
		return (TRUE);
	return (FALSE);
}

int	err_free_date(int yr, int mth, int dt)
{
	if (is_leap_year(yr) == FALSE)
		if (mth == 2 && dt > 28)
			return (FORMAT_ERR("Only 28 days in Feb for non-leap years."), FALSE);

	if ((mth == 4 || mth == 6 || mth == 9 || mth == 11) && dt > 30)
		return (FORMAT_ERR("Only 30 days in Apr, Jun, Sept and Nov."), FALSE);

	return (TRUE);
}

int	validate_date(std::string date, std::map<std::string, float> &btc_rate)
{
	std::stringstream	date_stream(date);
	std::string	token;
	int	num = 0;
	int	yr;
	int	mth;
	int	dt;
	while (std::getline(date_stream, token, '-'))
	{
		if (token.find_first_not_of(" ") == std::string::npos)
			return (FORMAT_ERR("\'" + date + "\'" + " not in line with the date format `YYYY-MM-DD`: < 3 tokens or all spaces for either"), FALSE);
		if (num == 0 && validate_ymd(token, 'Y') == FALSE)
			return (FALSE);
		else if (num == 0)
			yr = atoi(token.c_str());
		if (num == 1 && validate_ymd(token, 'M') == FALSE)
			return (FALSE);
		else if (num == 1)
			mth = atoi(token.c_str());
		if (num == 2 && validate_ymd(token, 'D') == FALSE)
			return (FALSE);
		else if (num == 2)
			dt = atoi(token.c_str());
		num++;
	}
	if (err_free_date(yr, mth, dt) == FALSE)
		return (FALSE);
	if (num != 3)
		return (FORMAT_ERR("\'" + date + "\'" + " not in line with the date format `Y-M-D`: no delim"), FALSE);
	btc_rate[date];
	return (TRUE);
}

int	validate_value(std::string value, std::map<std::string, float> &btc_rate, std::string k)
{
	// non-digits are converted to 0
	float	val = std::strtof(value.c_str(), NULL);
	if (!(val > 0.0f && val < 100.0f))
		return (FORMAT_ERR("\'" + value + "\'" + " not in line with the value format `(0, 100)`"), FALSE);

	btc_rate[k] = val;
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

int	err_free_line(char *database, std::map<std::string, float> &btc_rate)
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
		std::string k;
		while (std::getline(line_stream, token, '|'))
		{
			if (token.find_first_not_of(" ") == std::string::npos)
				return (FORMAT_ERR("\'" + line + "\'" + " not in line with the format `date | value`: < 2 tokens or all spaces for either"), FALSE);

			std::string	trimmed_token = trim_str(token);
			if (!trimmed_token.compare("date"))
				num_header_d += 1;
			else if (num_pipe == 0)
			{
				k = trimmed_token;
				if (validate_date(trimmed_token, btc_rate) == FALSE)
					return (FALSE);
			}
			if (!trimmed_token.compare("value"))
				num_header_v += 1;
			else if (num_pipe == 1)
			{
				if (validate_value(trimmed_token, btc_rate, k) == FALSE)
					return (FALSE);
			}

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
	//std::map<time_t, float>	btc_rate;
	std::map<std::string, float>	btc_rate;

	if (err_free_arg(argv, argc) == FALSE)
		return (FORMAT_ERR("Usage: ./btc [filename].txt"), 1);
	if (err_free_line(argv[1], btc_rate) == FALSE)
		return (1);

	//print hash map in accordance with c98
	for (std::map<std::string, float>::iterator i = btc_rate.begin(); i != btc_rate.end(); i++)
		std::cout << i->first << " => " << i->second << std::endl;

	return (0);
}
