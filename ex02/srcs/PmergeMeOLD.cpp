/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeOLD.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:23:56 by mgagne            #+#    #+#             */
/*   Updated: 2024/10/02 01:11:40 by mgagne           ###   ########.fr       */
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



std::vector<std::pair<long, long> > fillVectorPair(std::vector<long> v)
{
	std::vector<std::pair<long, long> > vPair;

	for (size_t i = 0; i < v.size(); i++)
	{
		if (i % 2 == 1)
		{
			if (v[i] < v[i - 1])
				std::swap(v[i], v[i - 1]);
			vPair.push_back(std::make_pair(v[i], v[i - 1]));
		}
	}
	// if (v.size() % 2 != 0)
	// 	vPair.push_back(std::make_pair(v[v.size() - 1], -1));
	return (vPair);
}

std::vector<std::pair<long, long> > makePair(std::vector<std::pair<long, long> > vPair)
{
	std::vector<std::pair<long, long> > vPair2;

	for (size_t i = 0; i < vPair.size(); i++)
	{
		if (i % 2 == 1)
		{
			if (vPair[i].first < vPair[i - 1].first)
				std::swap(vPair[i].first, vPair[i - 1].first);
			vPair2.push_back(std::make_pair(vPair[i].first, vPair[i - 1].first));
		}
	}
	// if (vPair.size() % 2 == 1 && vPair[vPair.size() - 1].second == -1)
	// 	vPair2.push_back(std::make_pair(vPair[vPair.size() - 1].first, -1));
	return (vPair2);
}

std::vector<long> vSort(std::vector<long> sorted, std::vector<std::pair<long, long> > vPair)
{
	std::vector<std::pair<long, long> > vec;

	if (vPair.size() != 1)
	{
		vec = makePair(vPair);
		sorted = vSort(sorted, vec);
	}
	if (vPair.size() == 1)
	{
		sorted.push_back(vPair[0].second);
		sorted.push_back(vPair[0].first);
		vPair.erase(vPair.begin());
	}

	if (vPair.size() >= 2)
		sorted = insertElements(sorted, vPair);
	return (sorted);
}

std::vector<long> insertElements(std::vector<long> sorted, std::vector<std::pair<long, long> > cur)
{
	std::size_t j;

	int un2 = 0;
	int un1 = 1;
	int index;

	while (!cur.empty())
	{
		j = Jacobsthal(un1, un2);
		un2 = un1;
		un1 = j;
		if (j > cur.size() - 1)
		{
			j = cur.size() - 1;
		}
		if (cur[cur.size() - 1].second == -1)
		{
			sorted = binarySearch(cur.size() - 1, cur[cur.size() - 1].first, sorted);
			cur.erase(cur.size() - 1);
		}
		while (j != std::string::npos)
		{
			// if (cur[j].second == -1)
				// sorted = binarySearch(cur.size() - 1, cur[j].first, sorted);
			index = find_index(cur[j].first, sorted);
			sorted = binarySearch(index, cur[j].second, sorted);
			cur.erase(cur.begin() + j);
			j--;
		}
	}
	return (sorted);
}

	// if (old.size() * 2 != cur.size())
	// 	sorted.push_back(cur[cur.size() - 1].first);

int Jacobsthal(int cur, int last)
{
	return (cur + (2 * last));
}

std::vector<long> binarySearch(int right, int value, std::vector<long> sorted)
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
	return (sorted);
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
