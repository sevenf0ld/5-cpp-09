/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:45:55 by maiman-m          #+#    #+#             */
/*   Updated: 2024/07/23 13:56:12 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_zero.hh"

std::map<std::string, float> BitcoinExchange::btc_rate_;
const char	*BitcoinExchange::csv_ = "data.csv";
// to skip the c.str() when constructing file
//const std::string &BitcoinExchange::csv_ = "data.csv";

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
			// must be assignable and can overwrite
			//btc_rate_[date] = std::strtof(rate.c_str(), NULL);
			btc_rate_.insert(std::map<std::string, float>::value_type(date, std::strtof(rate.c_str(), NULL)));
			// c++ alt for the above
			//btc_rate_.insert({date, std::strtof(rate.c_str(), NULL)});
			// involve implicit type conversion
			//btc_rate_.insert(std::pair<std::string, float>(date, std::strtof(rate.c_str(), NULL)));
			//btc_rate_.insert(std::make_pair(date, std::strtof(rate.c_str(), NULL)));
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

		std::map<std::string, float>::iterator ite = btc_rate_.find(d);
		// gives the prev/lesser date but not used bc non-existing dates are not detected this way
		//std::map<std::string, float>::iterator ite = btc_rate.lower_bound(d);
		// gives the next/greater date
		//std::map<std::string, float>::iterator ite = btc_rate.upper_bound(d);
		if (ite != btc_rate_.end())
			std::cout << "key: " << ite->first << ", val: " << (ite->second) * v << std::endl;
		else
		{
			// gives the next/greater date
			ite = btc_rate_.lower_bound(d);
			// gives the next/greater date
			//ite = btc_rate.upper_bound(d);
			// decrement to the prev/lesser date
			ite--;
			if (ite != btc_rate_.end())
				if (!d.empty())
					std::cout << "key: " << d << ", val: " << (ite->second) * v << std::endl;
		}
	}
}

std::map<std::string, float> BitcoinExchange::get_btc_rate(void) const
{
	return (btc_rate_);
}
