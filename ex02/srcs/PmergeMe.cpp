/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:23:56 by mgagne            #+#    #+#             */
/*   Updated: 2024/10/01 14:42:44 by mgagne           ###   ########.fr       */
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

	for (int i = 1; i < argc; i++)
	{
		v.push_back(strtol(argv[i], NULL, 10));
		d.push_back(strtol(argv[i], NULL, 10));
	}
	printVector(v);
	v = sortVector(v);
	// printVector(v);
	// d = sortDeque(d, argc);
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

std::vector<long> vSort(std::vector<long> sorted, std::vector<std::pair<long, long> > vPair)
{

	for (size_t i = 0; i < vPair.size(); i++)
	{
		if (vPair[i].second != -1 && vPair[i].first < vPair[i].second)
			std::swap(vPair[i].first, vPair[i].second);
	}

	std::vector<std::pair<long, long> > vPair2;

	if (vPair.size() >= 2)
	{
		std::cout << std::endl;
		for (size_t i = 0; i < vPair.size(); i++)
		{
			if ((i % 2 == 0 || i == 0) && i + 1 < vPair.size())
			{
				std::cout << "FIRST : " << vPair[i].first << " SECOND : " << vPair[i + 1].first << std::endl;
				vPair2.push_back(std::make_pair(vPair[i].first, vPair[i + 1].first));
			}
		}
	}
	if (vPair2.size() >= 2)
		sorted = vSort(sorted, vPair2);
	if (sorted.size() == 0 && vPair.size() == 1)
		sorted = insertElements(sorted, vPair);
	// sorted = insertElements(sorted, vPair);
	return (sorted);
}

std::vector<long> insertElements(std::vector<long> sorted, std::vector<std::pair<long, long> > vPair)
{
	std::cout << std::endl;
	for (size_t i = 0; i < vPair.size(); i++)
	{
		//jacobsthal - dichotomie
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
