#include "request.hpp"

bool Request::isRedirect(std::string path)
{
    if (r_redirects.find(path) != r_redirects.end())
        return true;
    else
        return false;
}

void Request::redirectURL(std::string path, int fd)
{
    std::string base = "HTTP/1.1 301 Moved Permanently\n";
    std::string body = "Location: " + r_redirects[path] + "\r\n";
    send(r_client_sockfd[fd], (base + body).c_str(), (base + body).size(), 0);
    return;
}