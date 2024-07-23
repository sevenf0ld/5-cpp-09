/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:45:55 by maiman-m          #+#    #+#             */
/*   Updated: 2024/07/23 19:17:14 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_zero.hh"

std::map<std::string, float>	BitcoinExchange::btc_rate_;
const char						*BitcoinExchange::csv_ = "data.csv";
std::string						BitcoinExchange::date_;
float							BitcoinExchange::value_ = 0.0f;

/* ============================================================================== */
/* 								rule of three									  */
/* ============================================================================== */
BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &rhs)
{
	(void) rhs;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
	(void) rhs;
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

/* ============================================================================== */
/* 							static parse member functions						  */
/* ============================================================================== */
void	BitcoinExchange::parse_database(void)
{
	std::ifstream	csv_file(csv_);
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
			btc_rate_.insert(std::map<std::string, float>::value_type(date, std::strtof(rate.c_str(), NULL)));
		}
		std::getline(csv_file, line);
	}
}

void	BitcoinExchange::parse_input(char *database)
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
		tm	conv;
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
				if (!strptime(trimmed_token.c_str(), "%Y-%m-%d", &conv))
				{
					FORMAT_ERR("\'" + trimmed_token + "\'" + " not in line with the date format `YYYY-MM-DD`: < 3 tokens or all spaces for either");
					break ;
				}
				else
				{
					if (err_free_date(conv) == FALSE)
						break ;
					BitcoinExchange::set_date(trimmed_token);
				}

			}
			if (!trimmed_token.compare("value"))
				num_header_v += 1;
			else if (num_pipe == 1)
			{
				float	val = std::strtof(trimmed_token.c_str(), NULL);
				if (!(val > 0.0f && val < 100.0f))
				{
					FORMAT_ERR("\'" + trimmed_token + "\'" + " not in line with the value format `(0, 100)`");
					break ;
				}
				else
					BitcoinExchange::set_value(val);
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

		std::map<std::string, float>::iterator ite = btc_rate_.find(BitcoinExchange::get_date());
		if (ite != btc_rate_.end())
			std::cout << ite;
		else
		{
			ite = btc_rate_.lower_bound(BitcoinExchange::get_date());
			ite--;
			if (ite != btc_rate_.end())
				if (!(BitcoinExchange::get_date().empty()))
					std::cout << ite;
		}

		std::getline(input_file, line);
	}
}

/* ============================================================================== */
/* 								static getters									  */
/* ============================================================================== */
std::string	BitcoinExchange::get_date(void)
{
	return (date_);
}

float	BitcoinExchange::get_value(void)
{
	return (value_);
}

/* ============================================================================== */
/* 								static setters									  */
/* ============================================================================== */
void	BitcoinExchange::set_date(std::string const date)
{
	date_ = date;
}

void	BitcoinExchange::set_value(float value)
{
	value_ = value;
}

/* ============================================================================== */
/* 									getters										  */
/* ============================================================================== */
std::map<std::string, float> BitcoinExchange::get_btc_rate(void) const
{
	return (btc_rate_);
}
