/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero_zero.hh                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:46:57 by maiman-m          #+#    #+#             */
/*   Updated: 2024/08/20 15:45:24 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZERO_ZERO_HH
#define ZERO_ZERO_HH

#define AC_BLACK "\x1b[30m"
#define AC_RED "\x1b[31m"
#define AC_GREEN "\x1b[32m"
#define AC_YELLOW "\x1b[33m"
#define AC_BLUE "\x1b[34m"
#define AC_MAGENTA "\x1b[35m"
#define AC_CYAN "\x1b[36m"
#define AC_WHITE "\x1b[37m"
#define AC_NORMAL "\x1b[m"
#define AC_BOLD "\033[1m"
#define AC_ITALIC "\033[3m"

#define TRUE 1
#define FALSE 0
#define YR 0
#define MN 1
#define DT 2

#define FORMAT_ERR(str) std::cerr << AC_RED << str << AC_NORMAL << std::endl

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <map>
#include <ctime>
#include <cctype>

#include "BitcoinExchange.hpp"

int err_free_arg(int argc, char **argv);

std::ostream &operator<<(std::ostream &out_stream, const std::map<std::string, float>::iterator &ite);
std::string trim_str(std::string &str);

#endif
