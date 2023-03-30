#include "webserv.hpp"

void    Webserv::notFound(int fd)
{

    std::string base = "HTTP/1.1 404 Not Found\n\n";
    std::ifstream   file("errors/404.html");
    std::stringstream   buff;

    buff << file.rdbuf();
    std::cout << buff << std::endl;
    std::string response = base + buff.str();
    send(this->client_sockfd[fd], response.c_str(), response.size(), 0);
}

void    Webserv::badMethod(int fd)
{

    std::string base = "HTTP/1.1 405 Method Not Allowed\n\n";
    std::ifstream   file("errors/405.html");
    std::stringstream   buff;

    buff << file.rdbuf();
    std::cout << buff << std::endl;
    std::string response = base + buff.str();
    send(this->client_sockfd[fd], response.c_str(), response.size(), 0);
}