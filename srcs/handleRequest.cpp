#include "../includes/webserv.hpp"


void    handleRequest(c_webserv *data, std::string buffer)
{
    s_request requestData;
    mainParsing(data, buffer, &requestData);
}