#include <iostream>

#include "server_conf.hpp"
#include "ParserJSON.hpp"

// HELPER
bool parse_words(ParserJSON const &json, std::vector<ParserJSON::t_lexem>::const_iterator const &word, std::vector<std::string> &words)
{
	std::string tmp;

	if (ParserJSON::to_word(json, word, tmp))
		return (true);
	words.push_back(tmp);
	return false;
}


// ROUTE
/*
	expect [int, string]
	throw error if duplicate int
*/
bool parse_default_error_pages(ParserJSON const &json,
															 std::vector<ParserJSON::t_lexem>::const_iterator const &error_page,
															 std::map<int, std::string> &default_error_pages)
{
	std::vector<ParserJSON::t_lexem>::const_iterator tmp = error_page;
	std::pair<int, std::string> pair;

	if (tmp->lexem != ParserJSON::OPEN_ARR)
		throw("error format default error_pages: expect [err_code, path_page]");
	++tmp;
	if (ParserJSON::to_number(json, tmp, pair.first))
		throw("error format default error_pages: expect [err_code, path_page]");
	++tmp;
	if (ParserJSON::to_word(json, tmp, pair.second))
		throw("error format default error_pages: expect [err_code, path_page]");
	++tmp;
	if (tmp->lexem != ParserJSON::CLOSE_ARR)
		throw("error format default error_pages: expect [err_code, path_page]");
	std::pair<std::map<int, std::string>::iterator, bool> ret = default_error_pages.insert(pair);
	if (!ret.second)
		throw("duplicate error_code encountered");
	return (false);
}

/*
	expect: POST | GET | DELETE
*/
bool parse_http_methods(ParserJSON const &json,
												std::vector<ParserJSON::t_lexem>::const_iterator const &method,
												std::vector<enum e_http_method> &methods)
{
	enum e_http_method tmp;

	(void)json;
	if (method->lexem != ParserJSON::WORD)
		return true;
	if (!method->value.compare("POST"))
		tmp = (enum e_http_method)POST;
	else if (!method->value.compare("GET"))
		tmp = (enum e_http_method)GET;
	else if (!method->value.compare("DELETE"))
		tmp = (enum e_http_method)DELETE;
	else
		throw ("unknown value in route methods");
	methods.push_back(tmp);
	return false;
}

bool parse_routes(ParserJSON const &json,
									std::vector<ParserJSON::t_lexem>::const_iterator const &route,
									std::vector<t_route> &routes)
{
	t_route rou;

	json.key("location", rou.location, ParserJSON::to_word, route);
	json.key_map("methods", rou.methods, parse_http_methods, route);
	json.key("http_redir", rou.http_redir, ParserJSON::to_word, route);
	json.key("root", rou.root, ParserJSON::to_word, route);
	json.key("dir_listing", rou.dir_listing, ParserJSON::to_bool, route);
	json.key("index", rou.index, ParserJSON::to_word, route);

	routes.push_back(rou);
	return (false);
}

// SERVER
/*
	every call to json.key inside an `if` means it's a required property json.key return true if failed
*/
bool parse_servers(ParserJSON const &json, std::vector<ParserJSON::t_lexem>::const_iterator const &server, std::vector<t_server> &servers)
{
	t_server serv;

	if (json.key("host", serv.host, ParserJSON::to_word, server))
		return true;
	if (json.key("port", serv.port, ParserJSON::to_number, server))
		return true;
	if (json.key_map("server_names", serv.server_names, parse_words, server))
		return true;
	if (json.key("max_client_body_size", serv.max_client_body_size, ParserJSON::to_number, server))
		return true;
	if (json.key_map("default_error_pages", serv.default_error_pages, parse_default_error_pages, server))
		return true;
	if (json.key_map("routes", serv.routes, parse_routes, server))
		return true;
	servers.push_back(serv);
	return (false);
}

std::vector<t_server> parse_configuration(std::string const &file_path)
{
	try
	{
		std::string file = read_file(file_path);
		ParserJSON json(file);

		std::cout << json.toString() << std::endl;
		std::vector<t_server> servers;
		if (json.key_map("servers", servers, parse_servers))
			throw("servers not found");

		for (std::vector<t_server>::const_iterator it = servers.begin(); it != servers.end(); ++it)
		{
			std::cout << "host " << it->host << std::endl;
			std::cout << "port " << it->port << std::endl;
			std::cout << "error_page " << std::endl;
			for (std::multimap<int, std::string>::const_iterator it_map = it->default_error_pages.begin(); it_map != it->default_error_pages.end(); ++it_map)
			{
				std::cout << it_map->first << ", " << it_map->second << std::endl;
			}
		}
		return servers;
	}
	catch (const char *err)
	{
		std::cerr << "parse_server_configuration_err" << std::endl;
		std::cerr << err << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "parse_server_configuration" << std::endl;
		std::cerr << e.what() << std::endl;
	}
	return std::vector<t_server>();
}