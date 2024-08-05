/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero_two.hh                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:38:11 by maiman-m          #+#    #+#             */
/*   Updated: 2024/08/05 11:12:35 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZERO_TWO_HH
#define ZERO_TWO_HH

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

#define FORMAT_ERR(str) std::cerr << AC_RED << str << AC_NORMAL << std::endl

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <climits>

#include "PmergeMe.hpp"

#endif
