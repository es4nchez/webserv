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

#include <dirent.h>

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
    std::vector<int>            _sockfd;
    std::vector<int>            _client_sockfd;
    std::vector<sockaddr_in>    _client_addr;
    std::vector<socklen_t>      _client_len;
    fd_set                      _fds;
    int                         _max_fd;

    // Request and serving file related
    std::string _index;
    std::string _rootpath;
    size_t      _maxBodySize;

    // Config file related
    std::string             _configPath;
    std::vector<int>        _ports;
    char                    **_wenvp;
    bool                    _dirListing;
    std::map<std::string, std::string> _redirects;

    // POST Data

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
    void    handleGET(s_request *requestData, int fd);
    void    handlePOST(std::string request, s_request *requestData, int fd);
    void    handleDELETE(s_request *requestData, int fd);

    // parsingRequestUtils.cpp
    void        getAddrMethodData(std:: string request, s_request *requestData);
    void        addQueryEnv(std::string str);
    std::string url_decode(const std::string& str);

    // sendResponse.cpp
    void    sendResponse(s_request *requestData, int fd, int success_code);
    void    sendIndex(int fd);

    // postRequest.cpp
    void            parsePostRequest(std::string request, int fd);
    std::string     parseBody(std::string request_body);
    std::string     getFilename(std::string request_data);

    // deleteRequest.cpp
    void            deleteRequest(s_request *requestData, int fd);

    // receive.cpp
    std::string receive(int i);
    std::string getRequestMethod(const std::string& headers);
    int         getContentLengthFromHeaders(const std::string& headers);

    // directoryListing.cpp
    void        directoryListing(s_request *requestData, int fd);
    std::string listFilesInDirectory(const std::string& directoryPath);

    // redirects.cpp
    bool        isRedirect(std::string path);
    void        redirectURL(std::string path, int fd);

    // errorResponses.cpp
    void    code_error(int fd, int error_code);
    void    badMethod(int fd);

};

#endif