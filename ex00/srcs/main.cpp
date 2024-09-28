/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:15:22 by mgagne            #+#    #+#             */
/*   Updated: 2024/09/28 15:02:36 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	std::string in;

	try
	{
		if (argc != 2)
			throw std::invalid_argument("invalid argument");

		BitcoinExchange	btc("./data.csv");
		btc.getInputData(argv[1]);
	}
	catch (std::invalid_argument const &err)
	{ std::cerr << err.what() << std::endl; }

	return (0);
}
