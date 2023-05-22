#include "request.hpp"

void    Request::code_error(int fd, int error_code)
{
    (void)fd;
	const std::string errorCodes[] = {"400 Bad Request", "404 Not Found", "405 Method Not Allowed", "413 Content Too Large"};
    const std::string errorFiles[] = {"www/errors/400.html", "www/errors/404.html", "www/errors/405.html", "www/errors/413.html"};
    const int errors[] = {400, 404, 405, 413};
    const int size = sizeof(errors) / sizeof(errors[0]);

    std::string base, name;
    for (int i = 0; i < size; ++i) {
        if (error_code == errors[i]) {
            base = "HTTP/1.1 " + errorCodes[i] + "\n\n";
            name = errorFiles[i];
            break;
        }
    }

    std::ifstream file(name.c_str());
    std::stringstream buff;
    buff << file.rdbuf();

    std::string response = base + buff.str();
    send(r_client_sockfd, response.c_str(), response.size(), 0);
}