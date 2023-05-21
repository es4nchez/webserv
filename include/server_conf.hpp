#ifndef SERVER_CONF_HPP
#define SERVER_CONF_HPP

#include <string>
#include <vector>

enum e_http_method
{
	GET,
	POST,
	DELETE
};

struct s_route
{
	std::string location;
	std::vector<enum e_http_method> methods;
	std::string http_redir;
	std::string root;
	bool dir_listing;
	std::vector<std::string> index;
} typedef t_route;

struct s_server
{
	std::string host;
	unsigned int port;
	std::vector<std::string> server_names;
	unsigned int max_client_body_size;
	std::vector<std::string> default_error_pages;
	std::vector<t_route> routes;
} typedef t_server;

struct s_conf_server
{
	std::vector<t_server> servers;
} typedef t_conf_server;

//readFileHelper.cpp
std::string read_file(std::string const &file_path);

#endif