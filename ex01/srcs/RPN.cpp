/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:23:56 by mgagne            #+#    #+#             */
/*   Updated: 2024/09/29 19:33:13 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

void parse(std::string s)
{
	std::size_t operators = 0;
	std::size_t nbs = 0;

	for (size_t i = 0; i < s.size(); i++)
	{
		if (i % 2 == 1)
		{
			if (s[i] != ' ')
				throw std::invalid_argument("invalid argument");
		}
		else
		{
			if (s[i] >= '0' && s[i] <= '9')
				nbs++;
			else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
				operators++;
			else
				throw std::invalid_argument("invalid argument 2");
		}
	}
	if ((nbs - 1 != operators) || nbs < 1 || operators < 1)
		throw std::invalid_argument("invalid argument 3");
	return ;
}

void startRpn(std::string  s)
{
	std::stack<int> stack;
	for (size_t i = 0; i < s.length(); i++)
	{
		if (isdigit(s[i]))
		{
			stack.push(std::atoi(s[i]));
		}
	}

}

void computeRpn()
{
	return ;
}

