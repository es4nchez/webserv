#include <set>
#include <utility>
#include <iostream>

#include "server_conf.hpp"

bool checkHost(std::string const &str)
{
	(void) str;
	return (false);
}

bool checkPort(unsigned int const &port)
{
	(void) port;
	return (false);
}

bool checkServerNames(std::vector<std::string> const &names)
{
	(void) names;
	return (false);
}

bool checkMaxBodySize(unsigned int const &size)
{
	(void) size;
	return (false);
}

bool checkErrorPages(std::map<int, std::string> const &pages)
{
	(void) pages;
	return (false);
}

bool checkServerConf(t_server const &server)
{
	std::set<std::string> locations;

	if (server.routes.size() == 0)
	{
		std::cerr << "checServerConf - server.routes should have at least one" << std::endl;
		return (true);
	}

	for (std::vector<t_route>::const_iterator it_route = server.routes.begin(); it_route != server.routes.end(); ++it_route)
	{
		std::pair<std::set<std::string>::iterator, bool> ret = locations.insert(it_route->location);
		if (!ret.second)
		{
			std::cerr << "checkServerConf - routes.location not unique";
			return (true);
		}
	}

	return (false);
}