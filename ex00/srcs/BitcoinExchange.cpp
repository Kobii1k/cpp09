/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:23:56 by mgagne            #+#    #+#             */
/*   Updated: 2024/09/28 20:05:58 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string in)
{
	try
	{
		parseCsv("data.csv");
		parseTxt(in);
	}
	catch (std::exception &err)
	{ std::cerr << "error: " << err.what() << std::endl; }
}

void BitcoinExchange::parseCsv(std::string csv)
{
	if (csv.substr(csv.length() - 4, csv.length()).compare(".csv") != 0)
		throw std::invalid_argument("bad file format");
}

void BitcoinExchange::parseTxt(std::string txt)
{

}
