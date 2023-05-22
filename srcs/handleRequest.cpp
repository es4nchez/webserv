#include "request.hpp"


void    Request::handleRequest(std::string buffer, int fd)
{
    s_request requestData;
	std::cout << buffer << std::endl;
    mainParsing(buffer, &requestData, fd);
}