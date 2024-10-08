/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:15:22 by mgagne            #+#    #+#             */
/*   Updated: 2024/10/01 19:57:34 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	try
	{
		if (argc <= 2)
			throw std::invalid_argument("This program takes multiple parameters");
		parseInput(argc, argv);
		mergeInsert(argc, argv);
	}
	catch (std::invalid_argument const &err)
	{
		std::cerr << "Error: " << err.what() << std::endl;
	}

	return 0;
}
