/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:45:48 by maiman-m          #+#    #+#             */
/*   Updated: 2024/07/23 14:07:38 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_zero.hh"

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

class BitcoinExchange
{
public:
	BitcoinExchange();
	~BitcoinExchange();

	static void	parse_database(void);
	static void	parse_input(char *database);

	std::map<std::string, float> get_btc_rate(void) const;

private:
	BitcoinExchange(const BitcoinExchange &rhs);
	BitcoinExchange &operator=(const BitcoinExchange &rhs);

	//std::map<time_t, float> btc_rate_;
	static std::map<std::string, float> btc_rate_;
	static const char *csv_;
};

#endif
