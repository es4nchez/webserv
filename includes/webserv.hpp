#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include <iostream>
#include <fstream>
#include <string>
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

void    handleRequest(char *buffer);
void    mainParsing(char *buffer, s_request *requestData);

#endif