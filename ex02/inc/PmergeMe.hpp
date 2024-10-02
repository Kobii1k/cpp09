/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:21:22 by mgagne            #+#    #+#             */
/*   Updated: 2024/10/02 01:59:38 by mgagne           ###   ########.fr       */
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
	std::vector<long> sortVector(std::vector<long> d);
	std::deque<long> sortDeque(std::deque<long> d);

	std::vector<long > fillPairs(std::vector<long> v, std::vector<std::pair<long, long> > &pairs);

	int Jacobsthal(int cur, int last);
	void binarySearch(int right, int value, std::vector<long> &sorted);
	int find_index(long value, std::vector<long> v);

#endif
