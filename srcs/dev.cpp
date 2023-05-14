#include "webserv.hpp"

void Webserv::HARDCODE_INIT(void)
{
    _index = "42lWatch.html";
    _rootpath = "www/";

    ports.push_back(8080);
    ports.push_back(8181);

    _dirListing = false;

    _redirect.push_back("www/redir.html");
}

void signal_callback_handler(int signum) {
    std::cout << "Caught signal, detaching sockets" << std::endl;

    for (unsigned int i = 0; i < g_webserv->ports.size(); i++) 
        close(g_webserv->sockfd[i]);

   for (unsigned int i = 0; i < g_webserv->ports.size(); i++)
   {
        if (g_webserv->client_sockfd[i] != -1)
            close(g_webserv->client_sockfd[i]);
    }  


    // Terminate program
    exit(signum);
}