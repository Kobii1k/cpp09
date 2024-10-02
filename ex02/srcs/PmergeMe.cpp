/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 01:10:39 by mgagne            #+#    #+#             */
/*   Updated: 2024/10/02 12:48:19 by mgagne           ###   ########.fr       */
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

void printVector_v(std::vector<long> myVec)
{
	int i = 0;

	for (std::vector<long>::iterator it = myVec.begin(); it != myVec.end(); it++)
	{
		std::cout << *it << " ";
		i++;
		if (i == 10 && myVec.size() > 100)
		{
			std::cout << "[...]";
			return ;
		}
	}
	std::cout << std::endl;
}

void mergeInsert(int argc, char *argv[])
{
	std::vector<long> vSorted;
	std::deque<long> dSorted;

	std::vector<std::pair<long, long> > v;
	std::deque<std::pair<long, long> > d;

	double time;

	struct timeval start_t, end_t;
	struct timeval start_t2, end_t2;

	for (int i = 1; i < argc; i++)
	{
		v.push_back(std::pair<long, long>(strtol(argv[i], NULL, 10), 0));
		d.push_back(std::pair<long, long>(strtol(argv[i], NULL, 10), 0));
	}

	gettimeofday(&start_t, NULL);
	vSorted = sortVector(v);
	gettimeofday(&end_t, NULL);
	time = (((end_t.tv_sec - start_t.tv_sec)) * 1000000 + (end_t.tv_usec - start_t.tv_usec) )/ 1000.0;
	std::cout << "Time for std::vector: " << time << " ms" << std::endl;
	std::cout << "Sorted vector:	";
	printVector_v(vSorted);
	std::cout << std::endl << std::endl;

	gettimeofday(&start_t2, NULL);
	dSorted = sortDeque(d);
	gettimeofday(&end_t2, NULL);
	time = (((end_t2.tv_sec - start_t2.tv_sec)) * 1000000 + (end_t2.tv_usec - start_t2.tv_usec) )/ 1000.0;
	std::cout << "Time for std::deque : " << time << " ms" << std::endl;
	std::cout << "Sorted Deque:	";
	printDeque(dSorted);
	std::cout << std::endl;
}

std::vector<long> sortVector(std::vector<std::pair<long, long> >  v)
{
	std::vector<long> sorted;
	std::vector<long> highest;
	std::vector<std::pair<long, long> > pairs;
	size_t jacob;
	int un1 = 1;
	int un2 = 0;

	fillPairs_v(v, pairs);
	if (pairs.size() > 1)
		sorted = sortVector(pairs);
	else
	{
		sorted.push_back(pairs[0].second);
		sorted.push_back(pairs[0].first);
		pairs.erase(pairs.begin());
	}
	while (!pairs.empty() || v.size() % 2 == 1)
	{
		jacob = Jacobsthal(un1, un2);
		un2 = un1;
		un1 = jacob;
		if (jacob >= pairs.size())
		{
			jacob = pairs.size() - 1;
			if (v.size() % 2 == 1)
			{
				binarySearch_v(sorted.size(), v[v.size() - 1].first, sorted);
				v.pop_back();
			}
		}
		while (jacob != std::string::npos)
		{
			int index = find_index_v(pairs[jacob].first, sorted);
			binarySearch_v(index, pairs[jacob].second, sorted);
			pairs.erase(pairs.begin() + jacob);
			jacob--;
		}
	}
	return (sorted);
}

void fillPairs_v(std::vector<std::pair<long, long> >  v, std::vector<std::pair<long, long> > &pairs)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		if (i % 2 == 1)
		{
			if (v[i].first < v[i - 1].first)
				std::swap(v[i].first, v[i - 1].first);
			pairs.push_back(std::make_pair(v[i].first, v[i - 1].first));
		}
	}
}

int Jacobsthal(int cur, int last)
{
	return (cur + (2 * last));
}

void binarySearch_v(int right, int value, std::vector<long> &sorted)
{
	int left = 0;
	int mid;

	while (left < right)
	{
		mid = (left + right) / 2;
		if (sorted[mid] < value)
			left = mid + 1;
		else
			right = mid;
	}
	sorted.insert(sorted.begin() + left, value);
}

int find_index_v(long value, std::vector<long> v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		if (value == v[i])
			return (i);
	}
	return (-1);
}


void printDeque(std::deque<long> dq)
{
	int i = 0;
	for (std::deque<long>::iterator it = dq.begin(); it != dq.end(); it++)
	{
		std::cout << *it << " ";
		i++;
		if (i == 10 && dq.size() > 100)
		{
			std::cout << "[...]";
			return ;
		}
	}
	std::cout << std::endl;
}

std::deque<long> sortDeque(std::deque<std::pair<long, long> > v)
{
	std::deque<long> sorted;
	std::deque<long> highest;
	std::deque<std::pair<long, long> > pairs;
	size_t jacob;
	int un1 = 1;
	int un2 = 0;

	fillPairs_d(v, pairs);
	if (pairs.size() > 1)
		sorted = sortDeque(pairs);
	else
	{
		sorted.push_back(pairs[0].second);
		sorted.push_back(pairs[0].first);
		pairs.erase(pairs.begin());
	}
	while (!pairs.empty() || v.size() % 2 == 1)
	{
		jacob = Jacobsthal(un1, un2);
		un2 = un1;
		un1 = jacob;
		if (jacob >= pairs.size())
		{
			jacob = pairs.size() - 1;
			if (v.size() % 2 == 1)
			{
				binarySearch_d(sorted.size(), v[v.size() - 1].first, sorted);
				v.pop_back();
			}
		}
		while (jacob != std::string::npos)
		{
			int index = find_index_d(pairs[jacob].first, sorted);
			binarySearch_d(index, pairs[jacob].second, sorted);
			pairs.erase(pairs.begin() + jacob);
			jacob--;
		}
	}
	return (sorted);
}

void fillPairs_d(std::deque<std::pair<long, long> >  v, std::deque<std::pair<long, long> > &pairs)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		if (i % 2 == 1)
		{
			if (v[i].first < v[i - 1].first)
				std::swap(v[i].first, v[i - 1].first);
			pairs.push_back(std::make_pair(v[i].first, v[i - 1].first));
		}
	}
}
void binarySearch_d(int right, int value, std::deque<long> &sorted)
{
	int left = 0;
	int mid;

	while (left < right)
	{
		mid = (left + right) / 2;
		if (sorted[mid] < value)
			left = mid + 1;
		else
			right = mid;
	}
	sorted.insert(sorted.begin() + left, value);
}

int find_index_d(long value, std::deque<long> v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		if (value == v[i])
			return (i);
	}
	return (-1);
}
