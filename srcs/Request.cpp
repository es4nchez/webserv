#include "request.hpp"

Request::Request(int client_sock_fd)
{
	r_index = "42lWatch.html";
    r_rootpath = "www/";
	r_dirListing = false;
    r_redirects["www/redir.html"] = "http://localhost:8080/42lWatch.html";
    r_maxBodySize = 10000;
	r_client_sockfd = client_sock_fd;

}

Request::~Request()
{

}

