#include "webserv.hpp"

void    Webserv::parsePostRequest(std::string request, int fd)
{
    (void) fd;

    std::cout << "POST : " << request << std::endl;
}