/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:23:56 by mgagne            #+#    #+#             */
/*   Updated: 2024/09/29 18:25:05 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

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
		std::cerr << "Error: " << err.what() << std::endl;
	}
	//empty db (+ structs in db) if not empty
}

void BitcoinExchange::parse(std::string file, int type)
{
	std::string line;
	std::ifstream inputFile;
	std::string format = file.substr(file.length() - 4, file.length());
	if (type && format.compare(".txt") != 0)
		throw std::invalid_argument("bad input file format, '.txt' accepted only");
	if (!type && format.compare(".csv") != 0)
		throw std::invalid_argument("bad database file format, '.csv' accepted only");
	inputFile.open(file.c_str(), std::ios::in);
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
			{ std::cerr << "Error: " << err.what() << std::endl; }
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
	for (size_t i = 0; i < 11; i++)
	{
		if (!std::isdigit(line[i]) && i != 4 && i != 7 && i != 10)
			throw std::invalid_argument("invalid content format of database file");
	}
	std::string value = line.substr(11, line.length());
	std::string date = line.substr(0, 10);
	checkDate(date);
	checkValue(value);
	this->db.insert(std::pair<std::string, float>(date, std::atof(value.c_str())));
	return ;
}

void BitcoinExchange::getInput(std::string line)
{
	if (line.at(4) != '-' || line.at(7) != '-' || line.empty() || line.length() < 14 || line.find(" | ") != 10)
		throw std::invalid_argument("invalid content format of input file");
	for (size_t i = 0; i < 11; i++)
	{
		if (!std::isdigit(line[i]) && i != 4 && i != 7 && i != 10)
			throw std::invalid_argument("invalid content format of input file");
	}
	std::string date = line.substr(0, 10);
	checkDate(date);
	checkValue(line.substr(13, line.length()));
	float amount = std::atof(line.substr(13, line.length()).c_str());
	if (amount < 0)
		throw   std::invalid_argument("value must be float or positive integer & between 0 and 1000");
	if (amount > 1000)
		throw std::invalid_argument("value must be float or positive integer & between 0 and 1000");
	useInput(date, amount);
}

void BitcoinExchange::useInput(std::string date, float amount)
{
	std::map<std::string, float>::iterator lower = this->db.upper_bound(date);
	if (lower == this->db.end())
		throw std::invalid_argument("value not found");
	if (lower != this->db.begin())
		lower--;
	std::cout << std::endl;
	std::cout << date << " == " << lower->first << std::endl;
	std::cout << date << " => " << amount << " = " << (amount * lower->second) << std::endl;
}

void BitcoinExchange::checkDate(std::string date)
{
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 6).c_str());
	int day = std::atoi(date.substr(8, 9).c_str());
	if (month < 1 || month > 12)
		throw std::invalid_argument("invalid date from file content");
	if (day < 1 || day > 31)
		throw std::invalid_argument("invalid date from file content");
	if (month <= 7 && month % 2 == 0 && day > 30)
		throw std::invalid_argument("invalid date from file content");
	if (month > 7 && month % 2 == 1 && day > 30)
		throw std::invalid_argument("invalid date from file content");
	if (month == 2)
	{
		if (year % 4 == 0 && year % 100 == 0 && year % 400 == 0)
		{
			if (day > 29)
				throw std::invalid_argument("invalid date from file content");
		}
		else if (day > 28)
			throw std::invalid_argument("invalid date from file content");
	}
	if ((day < 2 && month == 1 && year <= 2009) || year < 2009)
		throw std::invalid_argument("date value must be subsequent to 2009-01-03");
	return ;
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
