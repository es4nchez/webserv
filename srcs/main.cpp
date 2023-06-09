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
    ws.w_config = parse_configuration(ws._configPath);

    ws.w_client_addr.reserve(ws.w_config.size());

    sockaddr test;;

    if (ws.socketBinding())
        return (1);
    std::cout << std::endl
              << "\033[1;32mWebserv launching... start logs :\033[0m" << std::endl
              << std::endl;

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
                int sockfd = accept(ws.w_sockfd[i], &test, &ws.w_client_len[i]);
                if (sockfd < 0)
                {
                    std::cerr << "\033[1;31mError accepting connection\033[0m" << std::endl;
                    continue;
                }

                std::string request = ws.receive(i, sockfd);
                Request rt(sockfd, envp, ws.w_config[i]);
                // handle the request
                rt.handleRequest(request, i);

                // close the connection
                close(sockfd);
            }
        }
    }
    for (unsigned int i = 0; i < ws.w_config.size(); i++)
        close(ws.w_sockfd[i]);
    return (0);
}