#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <cmath>
#include <fstream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

struct s_request {

    std::string methd;
    std::string addr;

};


class c_webserv
{
    public:

    int client_sockfd;
};

void    handleRequest(c_webserv *data, std::string buffer);
void    mainParsing(c_webserv *data, std::string request, s_request *requestData);

#endif