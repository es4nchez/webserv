#include "webserv.hpp"
#include "ParserJSON.hpp"
#include "server_conf.hpp"
#include <array>

// For Dev
Webserv *g_webserv = nullptr;

int main(int ac, char **av, char **envp)
{
    Webserv ws;

    // Init args
    if (ws.args(ac, av, envp))
        return (1);

    // Parsing config file
	ws.w_config = parse_configuration(av[1]);

    // // HARDCODE CONFIG
    ws.HARDCODE_INIT();


    if (ws.socketBinding())
        return (1);
    std::cout << std::endl << "Webserv launching... start logs :" << std::endl << std::endl;

    while (true)
    {
        // wait for activity on the file descriptors using select()
        fd_set temp__fds = ws.w_fds;
        int ret = select(ws.w_max_fd + 1, &temp__fds, NULL, NULL, NULL);
        if (ret == -1)
        {
            std::cerr << "Error in select()" << std::endl;
            break;
        }

        // iterate over the file descriptors to check for activity
        for (unsigned int i = 0; i < ws.w_config.size(); i++)
        {
            if (FD_ISSET(ws.w_sockfd[i], &temp__fds))
            {
                // accept the incoming connection
                ws.w_client_sockfd[i] = accept(ws.w_sockfd[i], (sockaddr*) &ws.w_client_addr[i], &ws.w_client_len[i]);
                if (ws.w_client_sockfd[i] < 0) {
                    std::cerr << "Error accepting connection" << std::endl;
                    continue;
                }
  
                std::string request = ws.receive(i);
                std::cout << "clientsockfd : " << ws.w_client_sockfd[i] << std::endl;
                Request rt(ws.w_client_sockfd[i], envp, ws.w_config[i]);
                // handle the request
                rt.handleRequest(request, i);

                // close the connection
                close(ws.w_client_sockfd[i]);
            }
        }
    }
    for (unsigned int i = 0; i < ws.w_config.size(); i++)
        close(ws.w_sockfd[i]);
    return (0);
}