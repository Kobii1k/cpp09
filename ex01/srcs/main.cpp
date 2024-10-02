/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:15:22 by mgagne            #+#    #+#             */
/*   Updated: 2024/10/02 10:01:05 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int argc, char **argv)
{
	try
	{
		if (argc != 2)
			throw std::invalid_argument("This program takes 1 parameter");
		std::string s = argv[1];
		parse(s);
		startRpn(s);
	}
	catch (std::exception const &err)
	{ std::cerr << "Error: " << err.what() << std::endl;}

	return (0);
}
