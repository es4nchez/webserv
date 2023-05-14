#include "webserv.hpp"

bool Webserv::isRedirect(std::string path)
{
    if (std::find(redirect.begin(), redirect.end(), path) != redirect.end())
        return true;
    else
        return false;
}