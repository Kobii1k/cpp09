/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:21:22 by mgagne            #+#    #+#             */
/*   Updated: 2024/09/29 05:55:36 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
	#define BITCOINEXCHANGE_HPP

	#include "BitcoinExchange.h"

	class BitcoinExchange
	{
		private :
			std::map<std::string, double> db;
			BitcoinExchange();

		public :

			BitcoinExchange(std::string csv, std::string in);
			~BitcoinExchange();
			BitcoinExchange(BitcoinExchange const &copy);
			BitcoinExchange &operator=(BitcoinExchange const &copy);

			void parse(std::string file, int type);

			void storeData(std::string line);
			void getInput(std::string line);
			void useInput(std::string date, double amount);

			void checkDate(std::string date);
			void checkValue(std::string line);


	};

#endif
