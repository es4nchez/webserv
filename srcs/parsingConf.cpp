#include <iostream>

#include "server_conf.hpp"
#include "ParserJSON.hpp"

void parse_configuration(std::string const &file_path)
{
	try
	{
		std::string file = read_file(file_path);
		ParserJSON json(file);

		std::cout << json.toString() << std::endl;

		
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