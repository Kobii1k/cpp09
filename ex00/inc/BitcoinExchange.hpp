/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:21:22 by mgagne            #+#    #+#             */
/*   Updated: 2024/09/28 15:02:42 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
	#define BITCOINEXCHANGE_HPP

	#include "BitcoinExchange.h"

	class BitcoinExchange
	{
		private :
			std::map<float, std::string> db;
			BitcoinExchange();

		public :

			BitcoinExchange(std::string input);
			~BitcoinExchange();
			BitcoinExchange(BitcoinExchange const &copy);
			BitcoinExchange &operator=(BitcoinExchange const &copy);

			void parseCsv(std::string csv);
			void parseTxt(std::string txt);

			
	};

#endif
