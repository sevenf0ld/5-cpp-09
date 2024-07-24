/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero_one.hh                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:46:00 by maiman-m          #+#    #+#             */
/*   Updated: 2024/07/24 15:57:35 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZERO_ONE_HH
#define ZERO_ONE_HH

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
#define FORMAT_TEST(str) std::cout << AC_BOLD << AC_ITALIC << "[ " << str << " ]" << AC_NORMAL << std::endl

#include <iostream>
#include <stack>
#include <sstream>
#include <cstdlib>

#include "RPN.hpp"

#endif
