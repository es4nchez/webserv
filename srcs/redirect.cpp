#include "webserv.hpp"

bool Webserv::isRedirect(std::string path)
{
    if (std::find(_redirect.begin(), _redirect.end(), path) != _redirect.end())
        return true;
    else
        return false;
}