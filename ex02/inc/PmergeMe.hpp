/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:21:22 by mgagne            #+#    #+#             */
/*   Updated: 2024/10/02 12:16:40 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
	#define PMERGEME_HPP

	#include <iostream>
	#include <algorithm>
	#include <deque>
	#include <vector>
	#include <limits.h>
	#include <sys/time.h>


	void parseInput(int argc, char *argv[]);
	void mergeInsert(int argc, char *argv[]);


	void fillPairs_v(std::vector<std::pair<long, long> >  v, std::vector<std::pair<long, long> > &pairs);
	std::vector<long> sortVector(std::vector<std::pair<long, long> >  v);

	int Jacobsthal(int cur, int last);
	void binarySearch_v(int right, int value, std::vector<long> &sorted);
	int find_index_v(long value, std::vector<long> v);

	void fillPairs_d(std::deque<std::pair<long, long> >  v, std::deque<std::pair<long, long> > &pairs);
	std::deque<long> sortDeque(std::deque<std::pair<long, long> >  d);

	int Jacobsthal(int cur, int last);
	void binarySearch_d(int right, int value, std::deque<long> &sorted);
	int find_index_d(long value, std::deque<long> v);

	void printDeque(std::deque<long> dq);

#endif
