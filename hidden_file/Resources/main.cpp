/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 11:45:57 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/08 12:18:14 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>

void	crawl(const std::string &link)
{
	std::string	command = "wget ";
	std::string	command_2;

	command += link;
	command_2 = command + "README --quiet";
	command += " --quiet";
	system(command.c_str());
	system(command_2.c_str());

	std::ifstream	index_html_file;

	std::vector<std::string>	next_links;

	index_html_file.open("index.html");
	if (index_html_file.is_open())
	{

		std::string	line;
		while (getline(index_html_file, line))
		{
			if (!strncmp("<a href=\"", line.c_str(), sizeof("<a href=\"") - 1) && !strstr(line.c_str(), "README"))
			{
				std::string	next_link = link;

				next_link += line.substr(9, 27);
				next_links.push_back(next_link);
			}
		}

	}
	remove("index.html");

	std::ifstream	readme_file;
	readme_file.open("README");
	if (readme_file.is_open())
	{
		std::string	line;
		while (getline(readme_file, line))
		{
			std::cout << link << " " << line << std::endl;
		}

	}
	remove("README");

	for (std::string &next_link : next_links)
		crawl(next_link);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Usage: ./crawler <darkly_ip>" << std::endl;
		return (1);
	}

	crawl(av[1]);	
}
