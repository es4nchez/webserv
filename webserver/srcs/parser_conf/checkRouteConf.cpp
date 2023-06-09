#include <iostream>

#include "server_conf.hpp"

bool checkLocation(std::string const &str)
{
	if (str.empty())
	{
		std::cerr << "route.location: is empty" << std::endl;
		return true;
	}

	std::string::const_iterator it = str.begin();
	bool expect_char = true;

	if (*it != '/')
	{
		std::cerr << "route.location: expect / at start" << std::endl;
		return (true);
	}

	++it;
	for (; it != str.end(); ++it)
	{
		if (expect_char)
		{
			if (!isalnum(*it))
			{
				std::cerr << "route.location: expect [a-e,A-E,0-9]+" << std::endl;
				return (true);
			}
			else
				expect_char = false;
		}
		else if (*it == '/')
			expect_char = true;
	}

	return (false);
}

bool checkHttpRedir(std::string const &str)
{
	(void)str;
	return (false);
}

bool checkRoot(std::string const &str)
{
	(void)str;
	return (false);
}

bool checkIndex(std::string const &str)
{
	(void)str;
	return (false);
}

bool checkRouteConf(t_route const &route)
{
	(void)route;
	return false;
}