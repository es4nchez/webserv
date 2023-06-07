#ifndef SERVER_CONF_HPP
#define SERVER_CONF_HPP

#include <string>
#include <vector>
#include <map>

#include "ParserJSON.hpp"

enum e_http_method
{
	GET,
	POST,
	DELETE
};

struct s_route
{
	std::string location; //"/*/?"
	std::vector<enum e_http_method> methods;
	std::string http_redir; //"http://*.[a-z]*"
	std::string root; //word
	bool dir_listing;
	std::string index; //fichier
} typedef t_route;

struct s_server
{
	std::string host; //"dsadsadas" notdigit
	unsigned int port; //list
	std::vector<std::string> server_names; //"dsaadsa14512"
	unsigned int max_client_body_size;
	std::map<int, std::string> default_error_pages; //"fichier"
	std::vector<t_route> routes;
} typedef t_server;

struct s_conf_server
{
	std::vector<t_server> servers;
} typedef t_conf_server;

//parser_conf/parseHelpers.cpp
bool parse_words(ParserJSON const &json, std::vector<ParserJSON::t_lexem>::const_iterator const &word, std::vector<std::string> &words);
bool parse_word(ParserJSON const &json, std::vector<ParserJSON::t_lexem>::const_iterator const & word, std::string &dst);

//parser_conf/parsingConf.cpp
bool parse_configuration(std::string const &file_path, std::vector<t_server> &dst);

//parser_conf/checkServersConf.cpp
bool checkServersConf(std::vector<t_server> const &servers);

//parser_conf/parsingConfRoute.cpp
bool parse_routes(ParserJSON const &json,
									std::vector<ParserJSON::t_lexem>::const_iterator const &route,
									std::vector<t_route> &routes);
bool parse_http_methods(ParserJSON const &json,
												std::vector<ParserJSON::t_lexem>::const_iterator const &method,
												std::vector<enum e_http_method> &methods);
bool parse_default_error_pages(ParserJSON const &json,
															 std::vector<ParserJSON::t_lexem>::const_iterator const &error_page,
															 std::map<int, std::string> &default_error_pages);

//parser_conf/checkServerConf.cpp
bool checkServerConf(t_server const &server);
bool checkHost(std::string const &str);
bool checkPort(unsigned int const &port);
bool checkServerNames(std::vector<std::string> const &names);
bool checkMaxBodySize(unsigned int const &size);
bool checkErrorPages(std::map<int, std::string> const &pages);


//parser_conf/checkRouteConf.cpp
bool checkRouteConf(t_route const &route);
bool checkLocation(std::string const &str);
bool checkHttpRedir(std::string const &str);
bool checkRoot(std::string const &str);
bool checkIndex(std::string const &str);

//parser_conf/checkServersConf.cpp
bool checkServersConf(std::vector<t_server> const &servers);

//utils.cpp
bool string_to_word(std::string const &str, std::string &dst);
std::string trim_string(std::string const &str);
bool has_space(std::string const &str);
std::string read_file(std::string const &file_path);

#endif