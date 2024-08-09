/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_prog.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:14:43 by maiman-m          #+#    #+#             */
/*   Updated: 2024/08/10 01:48:23 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_two.hh"

#ifndef VALIDATE_PROG_HPP
#define VALIDATE_PROG_HPP

template <typename T>
int no_dup_seq(T const &container);

template <typename T>
int is_sorted_seq(T const &container);

template <typename T>
int is_odd(T const &container);

template <typename P, typename T>
P group_pairs(T const &container);

template <typename T>
void print_pair(T const &container);

#include "validate_prog.tpp"

#endif
