#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <cmath>
#include <vector>
#include <map>
#include <fstream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "cgi.hpp"

#define MAX_CONNECTIONS 10

// CGI
#define PYTHON "/usr/bin/python3"

// For dev
#include <signal.h>

struct s_request {

    std::string methd;
    std::string addr;
    std::map<std::string, std::string> data;

};


class Webserv
{
    public:

    Webserv();
    ~Webserv();

    // Socket related
    int                 sockfd[2];   //----------------------- << HARCOOOODE
    int                 client_sockfd[2]; //----------------------- << HARCOOOODE
    sockaddr_in         client_addr[2];
    socklen_t           client_len[2];
    fd_set              fds;
    int                 max_fd;

    // Request and serving file related
    std::string request;
    std::string index;
    std::string rootPath;

    // Config file related
    std::string configPath;
    std::vector<int>        ports;
    char                    **wenvp;
    std::map<std::string, std::string> env;

    // POST Data
    std::string query_string;

    // For dev
    void HARDCODE_INIT(void);

    // manageSockets.cpp
    int     socketBinding(void);

    // handleRequest.cpp
    void    handleRequest(std::string buffer, int fd);

    // args.cpp
    int     args(int ac, char **av, char **envp);

    // parsingRequest.cpp
    void    mainParsing(std::string request, s_request *requestData, int fd);
    void    getAddrMethodData(std:: string request, s_request *requestData);
    void    addQueryEnv(std::string str);

    // sendResponse.cpp
    void    sendResponse(s_request *requestData, int fd);
    void    sendIndex(int fd);

    // postRequest.cpp
    void            parsePostRequest(std::string request, int fd);
    std::string     parseBody(std::string request_body);
    std::string     getFilename(std::string request_data);

    // receive.cpp
    std::string receive(int i);
    std::string getRequestMethod(const std::string& headers);
    int         getContentLengthFromHeaders(const std::string& headers);

    // // cgi.cpp
    // void    handle_cgi_request(int sockfd, const std::string& query_string);
    // bool    is_cgi_request(const std::string& request_path);

    // errorResponses.cpp
    void    code_error(int fd, int error_code);
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
extern Webserv *g_webserv;

#endif