#include "../includes/webserv.hpp"


void    Webserv::handleRequest(std::string buffer, int fd)
{
    s_request requestData;
    mainParsing(buffer, &requestData, fd);
}