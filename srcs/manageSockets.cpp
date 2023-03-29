#include "../includes/webserv.hpp"

int socketBinding(c_webserv *data)
{

    // Create a socket
    for (unsigned int i = 0; i < data->ports.size(); i++)
    {
        data->sockfd[i] = socket(AF_INET, SOCK_STREAM, 0);
        if (data->sockfd[i] < 0)
        {
            std::cerr << "Error creating socket" << std::endl;
            return 1;
        }

        // Bind the socket to a port
        sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(data->ports[i]);
        if (bind(data->sockfd[i], (sockaddr*) &server_addr, sizeof(server_addr)) < 0)
        {
                std::cerr << "Error binding socket : " << data->sockfd << std::endl;
                return (1);
        }
        std::cout << "Socket '" << data->sockfd[i] << "' binded" << " to port " << data->ports[i] << std::endl;

        // Listen for incoming connections
        listen(data->sockfd[i], 5);

        // Accept incoming connections
        data->client_len = sizeof(data->client_addr);

    }

    return (0);
}