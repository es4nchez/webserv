#include "error.hpp"

error::error(int fd, std::map<int, std::string> error_code)
{
    e_fd = fd;
    const std::string errorCodes[] = {"400 Bad Request", "404 Not Found", "405 Method Not Allowed", "413 Content Too Large"};
    const std::string errorFiles[] = {"www/errors/400.html", "www/errors/404.html", "www/errors/405.html", "www/errors/413.html"};
    const int errors[] = {400, 404, 405, 413};
    const int size = sizeof(errors) / sizeof(errors[0]);
}

error::~error()
{

}

void    error::send_error(int error_code)
{

}