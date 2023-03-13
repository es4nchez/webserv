#include "../includes/webserv.hpp"


void    handleRequest(char *buffer)
{
    s_request requestData;
    mainParsing(buffer, &requestData);
}