#include "../includes/webserv.hpp"

int main(int ac, char **av)
{
    c_webserv data;

    // Init args
    if (args(&data, ac, av))
        return (1);

    // HARDCODE CONFIG
    data.port = 8080;
    data.index = "42lWatch.html";
    data.rootPath = "www/";

    // Parsing config file
  


    if (socketBinding(&data))
        return (1);

    std::cout << std::endl << "Webserv launching... start logs :" << std::endl << std::endl;
    while (true)
        {
            data.client_sockfd = accept(data.sockfd, (sockaddr*) &data.client_addr, &data.client_len);
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
        std::cout << "Received data from " << inet_ntoa(data.client_addr.sin_addr) << ":" << ntohs(data.client_addr.sin_port) << std::endl;
        
        // Handle request
        handleRequest(&data, buffer);

        // Close the connection
        close(data.client_sockfd);
    }
    close(data.sockfd);
    return (0);
}