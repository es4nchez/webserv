#include "webserv.hpp"

// For Dev
Webserv *g_webserv = nullptr;

int main(int ac, char **av, char **envp)
{
    Webserv ws;

    // For dev
    g_webserv = &ws;
    signal(SIGINT, signal_callback_handler);

    // Init args
    if (ws.args(ac, av, envp))
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
        // wait for activity on the file descriptors using select()
        fd_set temp_fds = ws.fds;
        int ret = select(ws.max_fd + 1, &temp_fds, NULL, NULL, NULL);
        if (ret == -1)
        {
            std::cerr << "Error in select()" << std::endl;
            break;
        }

        // iterate over the file descriptors to check for activity
        for (unsigned int i = 0; i < ws.ports.size(); i++)
        {
            if (FD_ISSET(ws.sockfd[i], &temp_fds))
            {
                // accept the incoming connection
                ws.client_sockfd[i] = accept(ws.sockfd[i], (sockaddr*) &ws.client_addr[i], &ws.client_len[i]);
                if (ws.client_sockfd[i] < 0) {
                    std::cerr << "Error accepting connection" << std::endl;
                    continue;
                }
  
                std::string request = ws.receive(i);

                // handle the request
                ws.handleRequest(request.c_str(), i);

                // close the connection
                close(ws.client_sockfd[i]);
            }
        }
    }

    for (unsigned int i = 0; i < ws.ports.size(); i++)
        close(ws.sockfd[i]);
    return (0);
}