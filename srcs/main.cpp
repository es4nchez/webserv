#include "../includes/webserv.hpp"

int main(int ac, char **av)
{
    c_webserv data;

    // For dev
    signal(SIGINT, signal_callback_handler);

    // Init args
    if (args(&data, ac, av))
        return (1);

    // HARDCODE CONFIG
    HARDCODE_INIT(&data);

    // Parsing config file
        // To do

    if (socketBinding(&data))
        return (1);
    std::cout << std::endl << "Webserv launching... start logs :" << std::endl << std::endl;

    while (true)
    {
        for (unsigned int i = 0; i < data.ports.size(); i++)
        {
            data.client_sockfd = accept(data.sockfd[i], (sockaddr*) &data.client_addr, &data.client_len);
            if (data.client_sockfd < 0)
            {
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
    }
    for (unsigned int i = 0; i < data.ports.size(); i++)
        close(data.sockfd[i]);
    return (0);
}