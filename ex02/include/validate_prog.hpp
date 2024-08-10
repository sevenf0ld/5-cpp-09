/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_prog.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:14:43 by maiman-m          #+#    #+#             */
/*   Updated: 2024/08/10 15:27:56 by maiman-m         ###   ########.fr       */
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

template <typename P>
void sort_descending(P &container_pairs);

template <typename P>
void merge_sort(P &container_pairs);

template <typename P>
void merge(P const &left, P const &right, P &container_pairs);

template <typename T, typename P>
T create_sorted_seq(P const &container_pairs);

template <typename T, typename P>
T create_pend_seq(P const &container_pairs);

template <typename P>
void print_pair(P const &container);

#include "validate_prog.tpp"

#endif
