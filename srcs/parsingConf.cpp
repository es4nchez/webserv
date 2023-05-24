#include <iostream>

#include "server_conf.hpp"
#include "ParserJSON.hpp"

bool parse_servers(std::vector<ParserJSON::t_lexem>::const_iterator it,
									 std::vector<ParserJSON::t_lexem> &arr_res)
{
	(void)arr_res;
	if (it->lexem != ParserJSON::BOOL)
		return true;
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

		std::vector<ParserJSON::t_lexem>::const_iterator key;
		if (json.get_key("test", key))
			throw "test key not found";

		std::vector<ParserJSON::t_lexem> arr_res;
		if (json.arr(key + 1, arr_res, parse_servers))
			throw "test arr fail";
		
		std::cout << arr_res.size() << std::endl;
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