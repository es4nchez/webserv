#include "../includes/webserv.hpp"

void HARDCODE_INIT(c_webserv *data)
{
    data->index = "42lWatch.html";
    data->rootPath = "www/";

    data->ports.push_back(8080);
    data->ports.push_back(8181);

    
}

void signal_callback_handler(int signum)
{
    std::cout << "Caught signal, detach-socket" << signum << std::endl;
    
    // Terminate program
    close(3);
    exit(signum);
}