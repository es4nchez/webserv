#include "webserv.hpp"

void Webserv::HARDCODE_INIT(void)
{
    _index = "42lWatch.html";
    _rootpath = "www/";

    _ports.push_back(8080);
    _ports.push_back(8181);

    _dirListing = false;

    _redirects["www/redir.html"] = "http://localhost:8080/42lWatch.html";

    _maxBodySize = 10000;


    _client_addr.reserve(_ports.size());
    _client_sockfd.reserve(_ports.size());

}