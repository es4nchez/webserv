#include "../includes/webserv.hpp"

int main(int ac, char **av)
{
    Webserv ws;

    // For dev
    signal(SIGINT, signal_callback_handler);

    // Init args
    if (ws.args(ac, av))
        return (1);

    // HARDCODE CONFIG
    ws.HARDCODE_INIT();

    // Parsing config file
        // To do
    
    if (ws.socketBinding())
        return (1);
    std::cout << std::endl << "Webserv launching... start logs :" << std::endl << std::endl;

    while (true)
    {
        for (unsigned int i = 0; i < ws.ports.size(); i++)
        {
            ws.client_sockfd[i] = accept(ws.sockfd[i], (sockaddr*) &ws.client_addr, &ws.client_len);
            if (ws.client_sockfd[i] < 0)
            {
                    std::cerr << "Error accepting connection" << std::endl;
                    continue;
            }

            // Receive ws from the client
            char buffer[1024];
            int bytes_received = recv(ws.client_sockfd[i], buffer, sizeof(buffer), 0);
            if (bytes_received < 0)
            {
                std::cerr << "Error receiving ws" << std::endl;
                continue;
            }

            // Print the received ws
            std::cout << "Received ws from " << inet_ntoa(ws.client_addr.sin_addr) << ":" << ntohs(ws.client_addr.sin_port) << std::endl;
            
            // Handle request
            ws.handleRequest(buffer, i);

            // Close the connection
            close(ws.client_sockfd[i]);
        }
    }
    for (unsigned int i = 0; i < ws.ports.size(); i++)
        close(ws.sockfd[i]);
    return (0);
}