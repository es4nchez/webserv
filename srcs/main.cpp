#include "../includes/webserv.hpp"

int main()
{
    c_webserv data;

    // Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Bind the socket to a port
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);
    if (bind(sockfd, (sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        return 1;
    }

    // Listen for incoming connections
    listen(sockfd, 5);

    // Accept incoming connections
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    std::cout << std::endl << "Webserv launching... start logs :" << std::endl << std::endl;
    while (true)
        {
            data.client_sockfd = accept(sockfd, (sockaddr*) &client_addr, &client_len);
            if (data.client_sockfd < 0) {
                std::cerr << "Error accepting connection" << std::endl;
                continue;
        }

        // Receive data from the client
        char buffer[1024];
        int bytes_received = recv(data.client_sockfd, buffer, sizeof(buffer), 0);
        if (bytes_received < 0)
        {
            std::cerr << "Error receiving data" << std::endl;
            continue;
        }

        // Print the received data
        std::cout << "Received data from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << std::endl;
        
        handleRequest(&data, buffer);

        // Send a response to the client
        // const char* response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\nHello World!";
        // send(client_sockfd, response, strlen(response), 0);

        // Close the connection
        close(data.client_sockfd);
    }
    close(sockfd);
    return (0);
}