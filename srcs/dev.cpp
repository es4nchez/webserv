#include "webserv.hpp"

void Webserv::HARDCODE_INIT(void)
{
    this->index = "42lWatch.html";
    this->rootPath = "www/";

    this->ports.push_back(8080);
    this->ports.push_back(8181);

    
}

void signal_callback_handler(int signum)
{
    std::cout << "Caught signal, detach-socket" << signum << std::endl;
    
    // Terminate program
    close(3);
    exit(signum);
}