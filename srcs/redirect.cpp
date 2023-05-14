#include "webserv.hpp"

bool Webserv::isRedirect(std::string path)
{
    if (_redirects.find(path) != _redirects.end())
        return true;
    else
        return false;
}

void Webserv::redirectURL(std::string path, int fd)
{
    std::string base = "HTTP/1.1 301 Moved Permanently\n";
    std::string body = "Location: " + _redirects[path] + "\r\n";
    send(_client_sockfd[fd], (base + body).c_str(), (base + body).size(), 0);
    return;
}