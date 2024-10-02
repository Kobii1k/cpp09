/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 01:10:39 by mgagne            #+#    #+#             */
/*   Updated: 2024/10/02 02:08:47 by mgagne           ###   ########.fr       */
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

void printVector(std::vector<long> myVec)
{
	int i = 0;
	for (std::vector<long>::iterator it = myVec.begin(); it != myVec.end(); it++)
	{
		std::cout << *it << " ";
		i++;
	}
	std::cout << std::endl;
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
	std::vector<long> sorted;
	std::vector<long> highest;
	std::vector<std::pair<long, long> > pairs;
	size_t jacob;
	int un1 = 1;
	int un2 = 0;

	highest = fillPairs(v, pairs);
	if (highest.size() > 1)
		sorted = sortVector(highest);
	else
	{
		sorted.push_back(pairs[0].second);
		sorted.push_back(pairs[0].first);
		pairs.erase(pairs.begin());
	}

	while (!pairs.empty())
	{
		jacob = Jacobsthal(un1, un2);
		un2 = un1;
		un1 = jacob;
		if (jacob > pairs.size() - 1)
		{
			jacob = pairs.size() - 1;
			if (v.size() % 2 == 1)
				binarySearch(sorted.size(), v[v.size() - 1], sorted);
		}
		while (jacob != std::string::npos)
		{
			int index = find_index(pairs[jacob].first, sorted);
			binarySearch(index, pairs[jacob].second, sorted);
			pairs.erase(pairs.begin() + jacob);
			jacob--;
		}
	}
	return (sorted);
}

std::vector<long > fillPairs(std::vector<long> v, std::vector<std::pair<long, long> > &pairs)
{
	std::vector<long> highest;

	for (size_t i = 0; i < v.size(); i++)
	{
		if (i % 2 == 1)
		{
			if (v[i] < v[i - 1])
				std::swap(v[i], v[i - 1]);
			pairs.push_back(std::make_pair(v[i], v[i - 1]));
			highest.push_back(v[i]);
		}
	}
	return (highest);
}

int Jacobsthal(int cur, int last)
{
	return (cur + (2 * last));
}

void binarySearch(int right, int value, std::vector<long> &sorted)
{
	int left = 0;
	int mid;

	while (left < right)
	{
		mid = left + (right - left) / 2;
		if (sorted[mid] < value)
			left = mid + 1;
		else
			right = mid;
	}
	sorted.insert(sorted.begin() + left, value);
}

int find_index(long value, std::vector<long> v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		if (value == v[i])
			return (i);
	}
	return (-1);
}
