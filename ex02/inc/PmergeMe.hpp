/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:21:22 by mgagne            #+#    #+#             */
/*   Updated: 2024/10/01 12:51:13 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
	#define PMERGEME_HPP

	#include <iostream>
	#include <algorithm>
	#include <deque>
	#include <vector>
	#include <limits.h>


	void parseInput(int argc, char *argv[]);
	void mergeInsert(int argc, char *argv[]);
	std::vector<long> sortVector(std::vector<long> d);
	std::deque<long> sortDeque(std::deque<long> d, int argc);
	std::vector<std::pair<long, long> > fillVectorPair(std::vector<long> v);
	std::vector<long> vSort(std::vector<long> sorted, std::vector<std::pair<long, long> > vPair);
	std::vector<long> insertElements(std::vector<long> sorted, std::vector<std::pair<long, long> > vPair);

#endif
