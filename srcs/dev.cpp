#include "webserv.hpp"

void Webserv::HARDCODE_INIT(void)
{

    w_ports.push_back(8080);
    w_ports.push_back(8181);

    w_client_addr.reserve(w_ports.size());
    w_client_sockfd.reserve(w_ports.size());

}