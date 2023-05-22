#include "webserv.hpp"

void Webserv::HARDCODE_INIT(void)
{
    w_config = new s_server[2];

    std::cout << "debug 1" << std::endl;

    s_route route;
    w_config[0].routes.push_back(route);

    w_config[0].routes[0].root = "www/";

    std::cout << "debug 2" << std::endl;


    w_ports.push_back(8080);
    w_ports.push_back(8181);

    w_client_addr.reserve(w_ports.size());
    w_client_sockfd.reserve(w_ports.size());

}