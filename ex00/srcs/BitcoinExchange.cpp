/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:23:56 by mgagne            #+#    #+#             */
/*   Updated: 2024/09/29 06:05:10 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <cctype>
#include <cstring>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

BitcoinExchange::BitcoinExchange(std::string csv, std::string in)
{
	try
	{
		parse(csv, 0);
		parse(in, 1);
	}
	catch (std::exception &err)
	{
		//empty db (+ structs in db) if not empty
		std::cerr << "error: " << err.what() << std::endl;
	}
	//empty db (+ structs in db) if not empty
}

void BitcoinExchange::parse(std::string file, int type)
{
	std::string line;
	std::string format = file.substr(file.length() - 4, file.length());
	if (type && format.compare(".txt") != 0)
		throw std::invalid_argument("bad input file format, '.txt' accepted only");
	if (!type && format.compare(".csv") != 0)
		throw std::invalid_argument("bad database file format, '.csv' accepted only");
	std::ifstream inputFile(file);
	if (!inputFile)
		throw std::invalid_argument("invalid database or input files");
	if (!inputFile.is_open())
		throw std::invalid_argument("couldn't open database or input files");
	std::getline(inputFile, line);
	while (std::getline(inputFile, line))
	{
		if (!type)
			storeData(line);
		else
		{
			try
			{
				getInput(line);
			}
			catch (std::exception &err)
			{ std::cerr << "error: " << err.what() << std::endl; }
		}
	}
	inputFile.close();
	return ;
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &copy)
{
	this->db = copy.db;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &copy)
{
	if (this == &copy)
		return (*this);
	this->db = copy.db;
	return (*this);
}

void BitcoinExchange::storeData(std::string line)
{
	if (line.at(4) != '-' || line.at(7) != '-' || line.at(10) != ',' || line.empty() || line.length() < 11)
		throw std::invalid_argument("invalid content format of database file");
	for (size_t i = 0; i < line.length(); i++)
	{
		if (!std::isdigit(line[i]) && i != 4 && i != 7 && i != 10)
			throw std::invalid_argument("invalid content format of database file");
	}
	std::string value = line.substr(11, line.length());
	std::string date = line.substr(0, 10);
	checkDate(date);
	checkValue(value);
	this->db.insert(std::pair<std::string, double>(date, std::stod(value)));
	return ;
}

void BitcoinExchange::getInput(std::string line)
{
	if (line.at(4) != '-' || line.at(7) != '-' || line.empty() || line.length() < 14 || line.substr(10, 12).compare(" | ") != 0)
		throw std::invalid_argument("invalid content format of input file");
	for (size_t i = 0; i < line.length(); i++)
	{
		if (!std::isdigit(line[i]) && i != 4 && i != 7 && i != 10 && i != 11 && i != 12)
			throw std::invalid_argument("invalid content format of input file");
	}
	std::string date = line.substr(0, 10);
	checkDate(date);
	checkValue(line.substr(14, line.length()));
	double amount = std::stod(line.substr(14, line.length()));
	if (amount < 0)
		throw   std::invalid_argument("value must be float or positive integer & between 0 and 1000");
	if (amount > 1000)
		throw std::invalid_argument("value must be float or positive integer & between 0 and 1000");
	useInput(date, amount);
}

void BitcoinExchange::useInput(std::string date, double amount)
{
	double value = 5;
	std::cout << date << " => " << amount << " = " << (amount * value) << std::endl;
}

void BitcoinExchange::checkDate(std::string date)
{
	int year = std::stoi(date.substr(0, 3));
	int month = std::stoi(date.substr(5, 6));
	int day = std::stoi(date.substr(8, 9));
}

void BitcoinExchange::checkValue(std::string line)
{
	bool dot = false;
	for (size_t i = 0; i < line.length(); i++)
	{
		if (!isdigit(line[i]))
		{
			if (dot || line[i] != '.' || i == line.length() - 1)
				std::invalid_argument("value must be float or positive integer & between 0 and 1000");
			dot = true;
		}

	}
}
