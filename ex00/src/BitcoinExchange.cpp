/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:45:55 by maiman-m          #+#    #+#             */
/*   Updated: 2024/08/20 22:51:11 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_zero.hh"

std::map<std::string, float> BitcoinExchange::btc_rate_;
const char *BitcoinExchange::csv_ = "data.csv";
std::string BitcoinExchange::date_;
float BitcoinExchange::value_ = 0.0f;

/* ============================================================================== */
/* 								rule of three									  */
/* ============================================================================== */
BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &rhs)
{
	(void)rhs;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
	(void)rhs;
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

/* ============================================================================== */
/* 							static validate helper functions					  */
/* ============================================================================== */
// check if dates passed as input are in YYYY-MM-DD format
static int err_free_date_len(std::string chunk, int flag)
{
	if (flag == YR && chunk.size() != 4)
	{
		FORMAT_ERR("\'" + chunk + "\'" + " not in line with the year format: YYYY");
		return (0);
	}
	if (flag == MN && chunk.size() != 2)
	{
		FORMAT_ERR("\'" + chunk + "\'" + " not in line with the month format: MM");
		return (0);
	}
	if (flag == DT && chunk.size() != 2)
	{
		FORMAT_ERR("\'" + chunk + "\'" + " not in line with the day format: DD");
		return (0);
	}

	return (1);
}

// check if the year given is a leap year
static int is_leap_year(int yr)
{
	if (yr % 400 == 0)
		return (TRUE);
	else if (yr % 100 == 0)
		return (FALSE);
	else if (yr % 4 == 0)
		return (TRUE);

	return (FALSE);
}

// check if the dates are in accordance with the calendar year
static int err_free_date(tm conv)
{
	if (is_leap_year(conv.tm_year + 1900) == FALSE)
		if (conv.tm_mon + 1 == 2 && conv.tm_mday > 28)
			return (FORMAT_ERR("Only 28 days in Feb for non-leap years."), FALSE);

	if ((conv.tm_mon + 1 == 4 || conv.tm_mon + 1 == 6 || conv.tm_mon + 1 == 9 || conv.tm_mon + 1 == 11) && conv.tm_mday > 30)
		return (FORMAT_ERR("Only 30 days in Apr, Jun, Sept and Nov."), FALSE);

	return (TRUE);
}

/* ============================================================================== */
/* 							static validate member functions					  */
/* ============================================================================== */
// ensure there is only one pipe with a space on either side as the delimiter
int BitcoinExchange::validate_delim(std::string line)
{
	std::size_t found = line.find("|");
	std::size_t r_found = line.rfind("|");
	if (found == std::string::npos || r_found == std::string::npos)
	{
		FORMAT_ERR("\'" + line + "\'" + " not in line with the format `date | value`: no delim");
		return (0);
	}
	if (found != r_found)
	{
		FORMAT_ERR("\'" + line + "\'" + " not in line with the format `date | value`: multi delims");
		return (0);
	}
	try
	{
		if (line.at(found - 1) != 32 || line.at(found + 1) != 32)
		{
			FORMAT_ERR("\'" + line + "\'" + " not in line with the format `date | value`: no space around delim");
			return (0);
		}
	}
	catch (const std::exception &e)
	{
		;
	}
	return (1);
}

int BitcoinExchange::validate_date(std::string line)
{
	std::string sub(line);
	int flag = YR;
	std::size_t found = sub.find('-');
	std::string tmp(sub.substr(0, found));
	// can't be reset to a sentinel value such as -1
	// while (found != std::string::npos)
	while (flag <= DT)
	{
		// YYYY-MM-DD
		if (err_free_date_len(tmp, flag) == 0)
			return (0);

		// reject non-digits (hyphen excluded as it acts as a delimiter and not part of Y/M/D validation)
		for (std::string::size_type i = 0; i < tmp.size(); i++)
		{
			if (!std::isdigit(tmp.at(i)))
			{
				FORMAT_ERR("\'" + tmp + "\'" + " not in line with the date format: non-digit");
				return (0);
			}
		}
		sub = sub.substr(found + 1);
		found = sub.find('-');
		// DD chunk as no delimiter should be present after
		if (found == std::string::npos)
			tmp = sub;
		else
			tmp = sub.substr(0, found);

		flag += 1;
	}

	tm conv;
	// check the format YYYY-MM-DD and maximum range
	if (!strptime(line.c_str(), "%Y-%m-%d", &conv))
	{
		FORMAT_ERR("\'" + line + "\'" + " not in line with the date format `YYYY-MM-DD`");
		return (0);
	}
	// check against the calendar year
	if (err_free_date(conv) == FALSE)
		return (0);

	BitcoinExchange::set_date(line);

	return (1);
}

int BitcoinExchange::validate_value(std::string line)
{
	float val = std::strtof(line.c_str(), NULL);

	// reject non-digits (negative's hyphen excluded; any standalone non-digits are converted to 0s by strtof)
	for (std::string::size_type i = 0; i < line.size(); i++)
	{
		if (!std::isdigit(line.at(i)) && val == 0.0f)
		{
			FORMAT_ERR("\'" + line + "\'" + " not in line with the value format: non-digit");
			return (0);
		}
	}

	// val must be from 1 to 999
	if (!(val > 0.0f && val < 1000.0f))
	{
		FORMAT_ERR("\'" + line + "\'" + " not in line with the value format `(0, 1000)`");
		return (0);
	}

	BitcoinExchange::set_value(val);

	return (1);
}

/* ============================================================================== */
/* 							static parse member functions						  */
/* ============================================================================== */
void BitcoinExchange::parse_database(void)
{
	std::ifstream csv_file(csv_);
	if (!csv_file)
	{
		FORMAT_ERR("Failed to open data.csv");
		return;
	}

	std::string line;
	std::size_t found;
	std::getline(csv_file, line);
	while (csv_file.good())
	{
		if (!(line.compare("date,exchange_rate")))
		{
			std::getline(csv_file, line);
			continue;
		}
		found = line.find(",");
		if (found != std::string::npos)
		{
			std::string date = line.substr(0, found);
			std::string rate = line.substr(found + 1);
			btc_rate_.insert(std::map<std::string, float>::value_type(date, std::strtof(rate.c_str(), NULL)));
		}
		std::getline(csv_file, line);
	}
}

void BitcoinExchange::parse_input(char *database)
{
	std::ifstream input_file(database);
	if (!input_file)
	{
		FORMAT_ERR("Failed to open " + std::string(database));
		return;
	}

	std::string line;
	std::getline(input_file, line);
	while (input_file.good())
	{
		if (BitcoinExchange::validate_delim(line) == 0)
		{
			std::getline(input_file, line);
			continue;
		}

		std::stringstream line_stream(line);
		std::string token;
		int num_pipe = 0;
		while (std::getline(line_stream, token, '|'))
		{
			// check if either side of the delimiter is not empty but consists of only spaces
			if (token.find_first_not_of(" ") == std::string::npos)
			{
				FORMAT_ERR("\'" + line + "\'" + " not in line with the format `date | value`: < 2 tokens or all spaces for either");
				break;
			}

			std::string trimmed_token = trim_str(token);
			if (trimmed_token.compare("date") != 0 && num_pipe == 0)
				if (BitcoinExchange::validate_date(trimmed_token) == 0)
					break;
			if (trimmed_token.compare("value") != 0 && num_pipe == 1)
				if (BitcoinExchange::validate_value(trimmed_token) == 0)
					break;

			num_pipe++;
		}

		if (num_pipe == 0 || num_pipe == 1)
		{
			std::getline(input_file, line);
			continue;
		}

		// if (num_pipe != 2)
		//{
		//	FORMAT_ERR("\'" + line + "\'" + " not in line with the format `date | value`: < 2 tokens or all spaces for either");
		//	return;
		// }

		// match date in input to database
		if (line.compare("date | value"))
			BitcoinExchange::match_date();

		std::getline(input_file, line);
	}
}

/* ============================================================================== */
/* 							static parse member functions						  */
/* ============================================================================== */
void BitcoinExchange::match_date(void)
{
	std::map<std::string, float>::iterator ite = btc_rate_.find(BitcoinExchange::get_date());
	// find returns end if it fails to find
	if (ite != btc_rate_.end())
		std::cout << ite;
	else
	{
		// return lower bound if fails to find
		ite = btc_rate_.lower_bound(BitcoinExchange::get_date());
		if (ite == btc_rate_.begin())
		{
			FORMAT_ERR("Date not found in database (lower bound absent).");
			return;
		}
		if (ite != btc_rate_.begin())
			ite--;
		if (ite != btc_rate_.end())
			if (!(BitcoinExchange::get_date().empty()))
				std::cout << ite;
	}
}

/* ============================================================================== */
/* 								static getters									  */
/* ============================================================================== */
std::string BitcoinExchange::get_date(void)
{
	return (date_);
}

float BitcoinExchange::get_value(void)
{
	return (value_);
}

/* ============================================================================== */
/* 								static setters									  */
/* ============================================================================== */
void BitcoinExchange::set_date(std::string const date)
{
	date_ = date;
}

void BitcoinExchange::set_value(float value)
{
	value_ = value;
}
