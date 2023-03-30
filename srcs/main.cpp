#include "webserv.hpp"

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

            // Accept a new incoming connection on the i-th port. 
            // It waits until a client connects to the port and returns a file descriptor client_sockfd for the new connection. 
            // The accept function takes as input the file descriptor sockfd for the i-th socket
            //  and fills in the client_addr struct with information about the client. 
            ws.client_sockfd[i] = accept(ws.sockfd[i], (sockaddr*) &ws.client_addr, &ws.client_len);
            if (ws.client_sockfd[i] < 0)
            {
                    std::cerr << "Error accepting connection" << std::endl;
                    continue;
            }

            // Receive data from the client on the i-th connection. 
            // It reads up to sizeof(buffer) bytes of data from the client_sockfd file descriptor into the buffer array. 
            // The function returns the number of bytes received.
            char buffer[1024];
            int bytes_received = recv(ws.client_sockfd[i], buffer, sizeof(buffer), 0);
            if (bytes_received < 0)
            {
                std::cerr << "Error receiving data" << std::endl;
                continue;
            }

            // Print a message to the console indicating that the program has received data from the client. 
            // It prints the IP address and port number of the client.
            std::cout << "Received data from " << inet_ntoa(ws.client_addr.sin_addr) << ":" << ntohs(ws.client_addr.sin_port) << std::endl;
            
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