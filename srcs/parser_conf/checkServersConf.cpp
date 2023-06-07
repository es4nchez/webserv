#include <set>
#include <utility>
#include <iostream>

#include "server_conf.hpp"

bool checkRouteConf(t_route const &route)
{
	if (route.location.empty())
	{
		std::cerr << "checkRouteConf - location should not be empty" << std::endl;
		return true;
	}
	return false;
}

bool checkServerConf(t_server const &server)
{
	std::set<std::string> locations;

	if (server.routes.size() == 0)
	{
		std::cerr << "checServerConf - routes should have at least one" << std::endl;
		return (true);
	}

	// check routes
	for (std::vector<t_route>::const_iterator it_route = server.routes.begin(); it_route != server.routes.end(); ++it_route)
	{
		if (checkRouteConf(*it_route))
			return true;

		std::pair<std::set<std::string>::iterator, bool> ret = locations.insert(it_route->location);
		if (!ret.second)
		{
			std::cerr << "checkServerConf - routes location not unique";
			return (true);
		}
	}

	return (false);
}

bool checkServersConf(std::vector<t_server> const &servers)
{
	std::set<unsigned int> ports;
	std::map<std::vector<t_server>::const_iterator, std::string> set_servers_names;

	for (std::vector<t_server>::const_iterator it = servers.begin(); it != servers.end(); ++it)
	{
		if (checkServerConf(*it))
			return (true);

		std::pair<std::set<unsigned int>::iterator, bool> set_ports_ret = ports.insert(it->port);
		if (!set_ports_ret.second)
		{
			std::cerr << "checkServersConf - servers port not unique" << std::endl;
			return (true);
		}

		for (std::vector<std::string>::const_iterator it_server_name = it->server_names.begin(); it_server_name != it->server_names.end(); ++it_server_name)
		{
			std::pair<std::map<std::vector<t_server>::const_iterator, std::string>::iterator, bool> set_servers_names_ret;
			set_servers_names_ret = set_servers_names.insert(std::pair<std::vector<t_server>::const_iterator, std::string>(it, *it_server_name));
			if (!set_servers_names_ret.second && it != set_servers_names_ret.first->first)
			{
				std::cerr << "checkServersConf - servers names not unique" << std::endl;
				return (true);
			}
		}
	}

	return false;
}