#include "../includes/webserv.hpp"

void    notFound(c_webserv *data)
{

    std::string base = "HTTP/1.1 404 Not Found\n\n";
    std::ifstream   file("errors/404.html");
    std::stringstream   buff;

    buff << file.rdbuf();
    std::cout << buff << std::endl;
    std::string response = base + buff.str();
    send(data->client_sockfd, response.c_str(), response.size(), 0);
}