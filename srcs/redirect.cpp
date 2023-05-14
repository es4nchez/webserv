#include "webserv.hpp"

bool Webserv::isRedirect(std::string path)
{
    if (_redirects.find(path) != _redirects.end())
        return true;
    else
        return false;
}