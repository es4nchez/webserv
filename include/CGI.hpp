#ifndef CGI_HPP
# define CGI_HPP

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

class CGI
{
    public:

    CGI();
    ~CGI();


    void handle_cgi_request(int sockfd, const std::string& cgi_path, char **wenvp);
    bool is_cgi_request(const std::string& request_path);


};

#endif