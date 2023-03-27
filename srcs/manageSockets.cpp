#include "../includes/webserv.hpp"

int socketBinding(c_webserv *data)
{

    // Create a socket
    data->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (data->sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }


    // Bind the socket to a port
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);
    if (bind(data->sockfd, (sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        return 1;
    }

    // Listen for incoming connections
    listen(data->sockfd, 5);

    // Accept incoming connections
    data->client_len = sizeof(data->client_addr);

    return (0);
}