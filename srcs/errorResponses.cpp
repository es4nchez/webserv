#include "../includes/webserv.hpp"

void    notFound(c_webserv *data)
{

    std::string response = "HTTP/1.1 404 Not Found\n\n404 NOT FOUND";
    
    send(data->client_sockfd, response.c_str(), response.size(), 0);
}