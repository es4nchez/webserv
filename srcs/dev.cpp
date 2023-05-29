#include "webserv.hpp"

void Webserv::HARDCODE_INIT(void)
{
    // w_config = new s_server[2];


    // s_route route;
    // w_config[0].routes.push_back(route);
    // w_config[0].routes[0].root = "www/";
    // w_config[0].routes[0].dir_listing = true;

    // w_config[1].routes.push_back(route);
    // w_config[1].routes[0].root = "www/";


    // w_ports.push_back(8080);
    // w_ports.push_back(8181);

    w_client_addr.reserve(w_config.size());
    w_client_sockfd.reserve(w_config.size());

}