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
#include <dirent.h>
#include "cgi.hpp"
#include "request.hpp"


#define MAX_CONNECTIONS 10

// CGI
#define PYTHON "/usr/bin/python3"

// For dev
#include <signal.h>

//parser
#include "server_conf.hpp"

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
    std::vector<int>            w_sockfd;
    std::vector<int>            w_client_sockfd;
    std::vector<sockaddr_in>    w_client_addr;
    std::vector<socklen_t>      w_client_len;
    fd_set                      w_fds;
    int                         w_max_fd;

    // Request and serving file related
    std::string _index;
    std::string _rootpath;
    size_t      _maxBodySize;

    // Config file related
    std::string             _configPath;
    std::vector<int>        w_ports;
    char                    **w_wenvp;
    bool                    _dirListing;
    std::map<std::string, std::string> _redirects;

    // POST Data

    // For dev
    void HARDCODE_INIT(void);

    // manageSockets.cpp
    int     socketBinding(void);

    // args.cpp
    int     args(int ac, char **av, char **envp);

    // receive.cpp
    std::string receive(int i);
    std::string getRequestMethod(const std::string& headers);
    int         getContentLengthFromHeaders(const std::string& headers);

};

#endif