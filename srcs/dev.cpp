#include "webserv.hpp"

void Webserv::HARDCODE_INIT(void)
{
    this->index = "42lWatch.html";
    this->rootPath = "www/";

    this->ports.push_back(8080);
    this->ports.push_back(8181);

    
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