/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:23:56 by mgagne            #+#    #+#             */
/*   Updated: 2024/10/01 18:49:07 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void parseInput(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
	{
		for (int j = 0; argv[i][j]; j++)
		{
			if (!isdigit(argv[i][j]))
				throw std::invalid_argument("Invalid argument: digits only");
		}
		if (strtol(argv[i], NULL, 10) > INT_MAX)
			throw std::invalid_argument("Invalid argument: too big a number, integers only");
	}

}

// std::deque<long> sortDeque(std::deque<long> d, int argc)
// {}

void printVector(std::vector<long> myVec)
{
	int i = 0;
	for (std::vector<long>::iterator it = myVec.begin(); it != myVec.end(); it++)
	{
		std::cout << "Value on index : " << i << " : " << *it << std::endl;
		i++;
	}
}

void mergeInsert(int argc, char *argv[])
{
	std::vector<long> v;
	std::deque<long> d;

	struct timeval start_t, end_t;
	gettimeofday(&start_t, NULL);
	gettimeofday(&end_t, NULL);

	for (int i = 1; i < argc; i++)
	{
		v.push_back(strtol(argv[i], NULL, 10));
		d.push_back(strtol(argv[i], NULL, 10));
	}

	printVector(v);
	gettimeofday(&start_t, NULL);
	v = sortVector(v);
	gettimeofday(&end_t, NULL);
	std::cout << std::endl;
	printVector(v);
	std::cout << "Time for std::vector : " << (end_t.tv_usec - start_t.tv_usec) << " us" << std::endl;

	// gettimeofday(&start_t, NULL);
	// d = sortDeque(d);
	// gettimeofday(&end_t, NULL);
	// std::cout << "Time for std::deque : " << (end_t.tv_usec - start_t.tv_usec) << " us" << std::endl;
}

std::vector<long> sortVector(std::vector<long> v)
{
	std::vector<std::pair<long, long> > vPair = fillVectorPair(v);
	std::vector<long> sorted;
	sorted = vSort(sorted, vPair);

	return (sorted);
}

std::vector<std::pair<long, long> > fillVectorPair(std::vector<long> v)
{
	std::vector<std::pair<long, long> > vPair;
	std::size_t len = v.size();

	for (size_t i = 0; i < len; i++)
	{
		if ((i % 2 == 0 || i == 0) && i + 1 < len)
			vPair.push_back(std::make_pair(v[i], v[i + 1]));
	}
	if (len % 2 != 0)
		vPair.push_back(std::make_pair(v[len - 1], -1));
	return (vPair);
}

std::vector<std::pair<long, long> > makePair(std::vector<std::pair<long, long> > vPair)
{
	std::vector<std::pair<long, long> > vPair2;

	if (vPair.size() >= 2)
	{
		for (size_t i = 0; i < vPair.size(); i++)
		{
			if ((i % 2 == 0 || i == 0) && i + 1 < vPair.size())
			{
				if (vPair[i].second != -1 && vPair[i].first < vPair[i].second)
					std::swap(vPair[i].first, vPair[i].second);
				vPair2.push_back(std::make_pair(vPair[i].first, vPair[i + 1].first));
			}
		}
	}
	return (vPair2);
}

std::vector<long> vSort(std::vector<long> sorted, std::vector<std::pair<long, long> > vPair)
{
	for (size_t i = 0; i < vPair.size(); i++)
	{
		if (vPair[i].second != -1 && vPair[i].first < vPair[i].second)
			std::swap(vPair[i].first, vPair[i].second);
	}

	std::vector<std::pair<long, long> > vPair2;
	vPair2 = makePair(vPair);

	if (vPair2.size() >= 2)
		sorted = vSort(sorted, vPair2);

	if (vPair2.size() == 1)
	{
		if (vPair2[0].second != -1 && vPair[0].first < vPair[0].second)
			std::swap(vPair2[0].first, vPair2[0].second);
		sorted.push_back(vPair2[0].second);
		sorted.push_back(vPair2[0].first);
	}
	if (vPair2.size() >= 1)
		sorted = insertElements(sorted, vPair, vPair2);

	return (sorted);
}

std::vector<long> insertElements(std::vector<long> sorted, std::vector<std::pair<long, long> > vPair, std::vector<std::pair<long, long> > vPair2)
{
	for (size_t i = 0; i < vPair.size(); i++)
	{
		if (vPair[i].second != -1)
			sorted.push_back(vPair[i].second);
	}
	std::cout << "vPair 2 size : " << vPair2.size() << std::endl;
	std::cout << "vPair size : " << vPair.size() << std::endl;
	if (vPair2.size() * 2 != vPair.size())
	{
		sorted.push_back(vPair[vPair.size() - 1].first);
	}
	return (sorted);
}

int Jacobsthal(int n)
{
	if (n == 0 || n == 1)
		return (n);
	else
		return (Jacobsthal(n - 1) + (2 * Jacobsthal(n - 2)));
}
