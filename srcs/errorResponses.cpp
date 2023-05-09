#include "webserv.hpp"

void    Webserv::code_error(int fd, int error_code)
{
	std::string base = "";
    std::string name = "";
	if (error_code == 404)
	{
		base = "HTTP/1.1 404 Not Found\n\n";
		name = "www/errors/404.html";
	}
	else if (error_code == 405)
	{
		base = "HTTP/1.1 405 Method Not Allowed\n\n";
    	name = "www/errors/405.html";
	}
    std::stringstream   buff;
	std::ifstream file(name);

    buff << file.rdbuf();
    std::cout << buff << std::endl;
    std::string response = base + buff.str();
    send(this->client_sockfd[fd], response.c_str(), response.size(), 0);
}
