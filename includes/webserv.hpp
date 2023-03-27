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

    // Socket related
    int         sockfd;
    int         client_sockfd;
    sockaddr_in client_addr;
    socklen_t   client_len;

    // Request and serving file related
    std::string request;
    std::string index;
    std::string rootPath;

    // Config file related
    std::string configPath;
    int         port;

};

// handleRequest.cpp
void    handleRequest(c_webserv *data, std::string buffer);

// parsingRequest.cpp
void    mainParsing(c_webserv *data, std::string request, s_request *requestData);

// sendResponse.cpp
void    sendResponse(c_webserv *data, s_request *requestData);
void    sendIndex(c_webserv *data);

// errorResponses.cpp
void    notFound(c_webserv *data);

// manageSockets.cpp
int     socketBinding(c_webserv *data);

// args.cpp
int     args(c_webserv *data, int ac, char **av);

#endif