#include <iostream>

#include "server_conf.hpp"
#include "ParserJSON.hpp"

bool parse_default_error_pages(ParserJSON const &json,
															 std::vector<ParserJSON::t_lexem>::const_iterator const &error_page,
															 std::map<int, std::string> &default_error_pages)
{
	static const std::string err = "server.default_error_pages: expect [err_code, path_page]";
	std::vector<ParserJSON::t_lexem>::const_iterator tmp = error_page;
	std::pair<int, std::string> pair;

	if (tmp->lexem != ParserJSON::OPEN_ARR)
	{
		std::cerr << err << std::endl;
		return (true);
	}
	++tmp;
	if (ParserJSON::to_number(json, tmp, pair.first))
	{
		std::cerr << err << std::endl;
		return true;
	}
	++tmp;
	if (ParserJSON::to_word(json, tmp, pair.second))
	{
		std::cerr << err << std::endl;
		return true;
	}
	++tmp;
	if (tmp->lexem != ParserJSON::CLOSE_ARR)
	{
		std::cerr << err << std::endl;
		return true;
	}
	std::pair<std::map<int, std::string>::iterator, bool> ret = default_error_pages.insert(pair);
	if (!ret.second)
	{
		std::cerr << "server.default_error_pages: duplicate err_code" << std::endl;
		return (true);
	}
	return (false);
}

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
		std::vector<t_server> servers;

		if (json.key_map("servers", servers, parse_servers))
			throw("servers not found");
		if (servers.size() == 0)
			throw ("no server config provided");
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