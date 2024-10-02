/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:23:56 by mgagne            #+#    #+#             */
/*   Updated: 2024/10/02 09:54:18 by mgagne           ###   ########.fr       */
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
				throw std::invalid_argument("arguments needs to be spaced out by ' '");
		}
		else
		{
			if (isdigit(s[i]))
				nbs++;
			else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
				operators++;
			else
				throw std::invalid_argument("accepted arguments are digits 0-9 and operators '+-/*'");
		}
	}
	if ((nbs - 1 != operators) || nbs < 1 || operators < 1)
		throw std::invalid_argument("Wrong syntax, bad number of operators or numbers");
	return ;
}

void startRpn(std::string  s)
{
	std::stack<int> stack;
	std::string operators = "+-*/";

	for (size_t i = 0; i < s.length(); i++)
	{
		if (operators.find(s[i]) != std::string::npos)
		{
			if (s[i] == '/' && stack.top() == 0)
				throw std::invalid_argument("come on... You can't divide by zero");
			if (stack.size() < 2)
				throw std::invalid_argument("not enough numbers to compute");
			computeRpn(&stack, s[i]);
		}
		else if (isdigit(s[i]))
		{
			std::string nbStr(1, s[i]);
			stack.push(std::atoi(nbStr.c_str()));
		}
	}
	std::cout << stack.top() << std::endl;
	return ;
}

void computeRpn(std::stack<int> *stack, char c)
{
	long long result;
	result = stack->top();
	stack->pop();
	switch(c)
	{
		case '+':
			result = stack->top() + result;
			break;
		case '-':
			result = stack->top() - result;
			break;
		case '*':
			result = stack->top() * result;
			break;
		default :
			result = stack->top() / result;
			break;
	}
	if (result < INT_MIN || result > INT_MAX)
		throw std::runtime_error("INT_MAX or INT_MIN value overflow");
	stack->pop();
	stack->push(result);
	return ;
}

