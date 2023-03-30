#include "webserv.hpp"

int Webserv::socketBinding(void)
{

    // Create a new socket file descriptor using the socket() system call. 
    // The first argument AF_INET specifies the address family (in this case, IPv4)
    // The second argument SOCK_STREAM specifies the socket type (in this case, a TCP stream socket)
    // The third argument 0 indicates that the protocol should be chosen automatically.
    for (unsigned int i = 0; i < this->ports.size(); i++)
    {
        this->sockfd[i] = socket(AF_INET, SOCK_STREAM, 0);
        if (this->sockfd[i] < 0)
        {
            std::cerr << "Error creating socket" << std::endl;
            return 1;
        }

        // This sets up the server address structure, server_addr, which will be used to bind the socket to a specific port. 

        // The sin_family member specifies the address family
        //  sin_addr.s_addr specifies the IP address to bind to (in this case, INADDR_ANY indicates that the socket
        // should listen on all available network interfaces)
        
        //sin_port specifies the port number to bind to (which is taken from the ports vector).

        // The bind() system call is then used to associate the socket file descriptor with the server address. 
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


        // Set the socket to listen for incoming connections.
        // The second argument to the listen() call specifies the size of the backlog queue,
        // which is the number of incoming connections that can be queued up before the system starts rejecting them. 

        // In this case, the backlog is set to 5. 
        // The client_len variable is also initialized to the size of the client_addr structure,
        // which will be used to store client connection information.
        listen(this->sockfd[i], 5);
        this->client_len = sizeof(this->client_addr);

    }

    return (0);
}