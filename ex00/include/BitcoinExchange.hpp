/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:45:48 by maiman-m          #+#    #+#             */
/*   Updated: 2024/08/20 16:59:55 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_zero.hh"

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

class BitcoinExchange
{
public:
	static int validate_delim(std::string line);
	static int validate_date(std::string line);
	static int validate_value(std::string line);

	static void parse_database(void);
	static void parse_input(char *database);

	static void match_date(void);

	static std::string get_date(void);
	static float get_value(void);

	static void set_date(std::string const date);
	static void set_value(float value);

private:
	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &rhs);
	BitcoinExchange &operator=(const BitcoinExchange &rhs);

	// std::map<time_t, float> btc_rate_;
	static std::map<std::string, float> btc_rate_;
	static const char *csv_;
	static std::string date_;
	static float value_;
};

#endif
