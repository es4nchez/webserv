#include <iostream>

#include "server_conf.hpp"
#include "ParserJSON.hpp"

bool parse_servers(std::vector<ParserJSON::t_lexem>::const_iterator it,
									 std::vector<ParserJSON::t_lexem> &arr_res)
{
	(void)arr_res;
	std::cout << "test: " << it->value << std::endl;
	return false;
}

void parse_configuration(std::string const &file_path)
{
	try
	{
		std::string file = read_file(file_path);
		ParserJSON json(file);

		std::cout << json.toString() << std::endl;

		std::vector<ParserJSON::t_lexem>::const_iterator tmp;

		if (json.key("servers", tmp))
		{
			std::cout << "servers key not found";
			return;
		}
		++tmp;

		std::vector<ParserJSON::t_lexem> arr_res;
		if (json.arr(tmp, arr_res, parse_servers))
		{
			std::cout << "json arr errror";
		}
		(void)tmp;
		std::cout << "Parsing done" << std::endl;
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
}