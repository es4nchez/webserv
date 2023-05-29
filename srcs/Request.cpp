#include "request.hpp"

Request::Request(int client_sock_fd, char **envp, s_server w_config)
{
        r_index = w_config.routes[0].index;
        r_rootpath = w_config.routes[0].root;
        r_dirListing = w_config.routes[0].dir_listing;
        r_redirects["www/redir.html"] = "http://localhost:8080/42lWatch.html";
        r_maxBodySize = 10000;
        r_client_sockfd = client_sock_fd;
        r_wenvp = envp;

    r_config = w_config;
}
Request::~Request()
{

}

