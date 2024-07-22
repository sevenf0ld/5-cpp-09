/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:45:38 by maiman-m          #+#    #+#             */
/*   Updated: 2024/07/22 16:02:25 by maiman-m         ###   ########.fr       */
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

void	parse_database(std::map<std::string, float> &btc_rate)
{
	std::ifstream	csv_file("data.csv");
	if (!csv_file)
	{
		FORMAT_ERR("Failed to open data.csv");
		return ;
	}

	std::string	line;
	std::size_t	found;

	std::getline(csv_file, line);
	while (csv_file.good())
	{
		if (line.compare("date,exchange_rate") == 0)
		{
			std::getline(csv_file, line);
			continue ;
		}
		found = line.find(",");
		if (found != std::string::npos)
		{
			std::string	date = line.substr(0, found);
			std::string	rate = line.substr(found + 1);
			btc_rate[date] = std::strtof(rate.c_str(), NULL);
		}
		std::getline(csv_file, line);
	}
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

int	validate_ymd(std::string token, char flag)
{
	int	digit = atoi(token.c_str());

	if (token.find_first_not_of("1234567890") != std::string::npos)
		return (FORMAT_ERR("\'" + token + "\'" + " not in line with the date format `YYYY-MM-DD`: non-digit present"), FALSE);

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


int	validate_date(std::string date, std::string &d)
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

	d = date;
	return (TRUE);
}

int	validate_value(std::string value, double *v)
{
	// non-digits are converted to 0
	float	val = std::strtof(value.c_str(), NULL);
	if (!(val > 0.0f && val < 100.0f))
		return (FORMAT_ERR("\'" + value + "\'" + " not in line with the value format `(0, 100)`"), FALSE);

	*v = val;
	return (TRUE);
}

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

void	parse_input(char *database, std::map<std::string, float> btc_rate)
{
	std::ifstream	input_file(database);
	if (!input_file)
	{
		FORMAT_ERR("Failed to open " + std::string(database));
		return ;
	}

	std::string	line;
	std::size_t	found;
	int	num_header_d = 0;
	int	num_header_v = 0;

	std::getline(input_file, line);
	while (input_file.good())
	{
		found = line.find("|");
		std::size_t	r_found = line.rfind("|");
		if (found == std::string::npos || r_found == std::string::npos)
		{
			FORMAT_ERR("\'" + line + "\'" + " not in line with the format `date | value`: no delim");
			std::getline(input_file, line);
			continue ;
		}
		if (found != r_found)
		{
			FORMAT_ERR("\'" + line + "\'" + "not in line with the format `date | value`: multi delims");
			std::getline(input_file, line);
			continue ;
		}

		std::stringstream	line_stream(line);
		std::string	token;
		int	num_pipe = 0;
		std::string	d;
		double	v;
		while (std::getline(line_stream, token, '|'))
		{
			if (token.find_first_not_of(" ") == std::string::npos)
			{
				FORMAT_ERR("\'" + line + "\'" + " not in line with the format `date | value`: < 2 tokens or all spaces for either");
				break ;
			}

			std::string	trimmed_token = trim_str(token);
			if (!trimmed_token.compare("date"))
				num_header_d += 1;
			else if (num_pipe == 0)
			{
				if (validate_date(trimmed_token, d) == FALSE)
					break ;
			}
			if (!trimmed_token.compare("value"))
				num_header_v += 1;
			else if (num_pipe == 1)
			{
				if (validate_value(trimmed_token, &v) == FALSE)
					break ;
			}

			num_pipe++;
		}


		if (num_pipe == 0 || num_pipe == 1)
		{
			std::getline(input_file, line);
			continue ;
		}

		if (num_header_d != 1 || num_header_v != 1)
		{
			FORMAT_ERR("not in line with the file format: multiple header dates or values");
			return ;
		}
		if (num_pipe != 2)
		{
			FORMAT_ERR("\'" + line + "\'" + " not in line with the format `date | value`: < 2 tokens or all spaces for either");
			return ;
		}

		std::getline(input_file, line);

		std::map<std::string, float>::iterator it = btc_rate.find(d);
		// gives the prev/lesser date but not used bc non-existing dates are not detected this way
		//std::map<std::string, float>::iterator it = btc_rate.lower_bound(d);
		// gives the next/greater date
		//std::map<std::string, float>::iterator it = btc_rate.upper_bound(d);
		if (it != btc_rate.end())
			std::cout << "key: " << it->first << ", val: " << (it->second) * v << std::endl;
		else
		{
			// gives the next/greater date
			it = btc_rate.lower_bound(d);
			// gives the next/greater date
			//it = btc_rate.upper_bound(d);
			// decrement to the prev/lesser date
			it--;
			if (it != btc_rate.end())
				if (!d.empty())
					std::cout << "key: " << d << ", val: " << (it->second) * v << std::endl;
		}
	}
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

	//std::map<time_t, float>	btc_rate;
	std::map<std::string, float>	btc_rate;
	parse_database(btc_rate);
	// print hash map in accordance with c98
	//for (std::map<std::string, float>::iterator i = btc_rate.begin(); i != btc_rate.end(); i++)
	//	std::cout << i->first << " => " << i->second << std::endl;

	parse_input(argv[1], btc_rate);

	return (0);
}
