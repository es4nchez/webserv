#include "webserv.hpp"

void    Webserv::parsePostRequest(std::string request, int fd)
{
    (void) fd;

    std::string request_body = request.substr(request.find("\r\n\r\n") + 4);

    std::cout << "Post data : " << request_body << std::endl;
}   