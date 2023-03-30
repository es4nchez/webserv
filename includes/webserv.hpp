#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <cmath>
#include <vector>
#include <fstream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// For dev
#include <signal.h>

struct s_request {

    std::string methd;
    std::string addr;

};


class Webserv
{
    public:

    Webserv();
    ~Webserv();

    // Socket related
    int         sockfd[2];   //----------------------- << HARCOOOODE
    int         client_sockfd[2]; //----------------------- << HARCOOOODE
    sockaddr_in client_addr;
    socklen_t   client_len;

    // Request and serving file related
    std::string request;
    std::string index;
    std::string rootPath;

    // Config file related
    std::string configPath;
    std::vector<int>        ports;




    // For dev
    void HARDCODE_INIT(void);

    // manageSockets.cpp
    int     socketBinding(void);

    // handleRequest.cpp
    void    handleRequest(std::string buffer, int fd);

    // args.cpp
    int     args(int ac, char **av);

    // parsingRequest.cpp
    void    mainParsing(std::string request, s_request *requestData, int fd);

    // sendResponse.cpp
    void    sendResponse(s_request *requestData, int fd);
    void    sendIndex(int fd);

    // errorResponses.cpp
    void    notFound(int fd);
    void    badMethod(int fd);

};


// // parsingRequest.cpp
// void    mainParsing(c_webserv *data, std::string request, s_request *requestData, int fd);

// // sendResponse.cpp
// void    sendResponse(c_webserv *data, s_request *requestData, int fd);
// void    sendIndex(c_webserv *data, int fd);

// // errorResponses.cpp
// void    notFound(c_webserv *data, int fd);
// void    badMethod(c_webserv *data, int fd);

// // manageSockets.cpp
// int     socketBinding(c_webserv *data);


// For dev
void signal_callback_handler(int signum);

#endif 