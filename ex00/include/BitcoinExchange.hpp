/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:45:48 by maiman-m          #+#    #+#             */
/*   Updated: 2024/07/23 16:54:51 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_zero.hh"

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

class BitcoinExchange
{
public:
	static void	parse_database(void);
	static void	parse_input(char *database);
	static std::string	get_date(void);
	static float		get_value(void);
	static void	set_date(std::string const date);
	static void	set_value(float value);

	std::map<std::string, float> get_btc_rate(void) const;

private:
	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &rhs);
	BitcoinExchange &operator=(const BitcoinExchange &rhs);

	//std::map<time_t, float> btc_rate_;
	static std::map<std::string, float> btc_rate_;
	static const char *csv_;

	static std::string	date_;
	static float		value_;
};

#endif
