#include "../includes/webserv.hpp"

int Webserv::socketBinding(void)
{

    // Create a socket
    for (unsigned int i = 0; i < this->ports.size(); i++)
    {
        this->sockfd[i] = socket(AF_INET, SOCK_STREAM, 0);
        if (this->sockfd[i] < 0)
        {
            std::cerr << "Error creating socket" << std::endl;
            return 1;
        }

        // Bind the socket to a port
        sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(this->ports[i]);
        if (bind(this->sockfd[i], (sockaddr*) &server_addr, sizeof(server_addr)) < 0)
        {
                std::cerr << "Error binding socket : " << this->sockfd[i] << std::endl;
                return (1);
        }
        std::cout << "Socket '" << this->sockfd[i] << "' binded" << " to port " << this->ports[i] << std::endl;

        // Listen for incoming connections
        listen(this->sockfd[i], 5);

        // Accept incoming connections
        this->client_len = sizeof(this->client_addr);

    }

    return (0);
}